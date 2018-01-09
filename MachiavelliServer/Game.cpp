#include "stdafx.h"
#include "Game.h"

void Game::addClient(shared_ptr<ClientInfo> client)
{
	auto &player = client->get_player();

	if (clients.size() >= 2) {
		player.notify("There are too much players in this game.");
		player.notify("Please try joining later.");
		return;
	}

	notifyAllPlayers("Player '" + player.get_name() + "' has joined the game.");
	
	clients.push_back(client);
	player.setWaiting(true);

	player.notify("You successfully joined a game.");
	player.notify("The game currently consists of you and " + to_string(getClientsAmount() - 1) + " other players.");

	if (clients.size() > 1) {
		start();
	}
	else {
		player.notify("Please wait, the game will begin when there are enough players.");
	}

}

void Game::notifyAllPlayers(string message)
{
	for (auto& otherClient : clients) {
		otherClient->get_player().notify(message);
	}
}

void Game::allPrompt()
{
	for (auto& otherClient : clients) {
		otherClient->get_player().prompt();
	}
}

void Game::removeClient(ClientInfo & client)
{
	for (auto it = clients.begin(); it != clients.end();)
	{
		if ((*it)->get_socket().get_socket() == client.get_socket().get_socket()) {
			it = clients.erase(it);
			notifyAllPlayers("Player '" + client.get_player().get_name() + "' has left the game.");
		}
		else {
			++it;
		}
	}

	if (clients.size() < 2) {
		for (auto it = clients.begin(); it != clients.end(); it = clients.begin())
		{
			auto &player = (*it)->get_player();
			player.setWaiting(false);
			player.notify("The game doesn't have enough players to keep playing...");
			player.notify("You win!");
			player.prompt();
			removeClient(*(*it));
		}
		finished = true;
	}
}

bool Game::hasClient(ClientInfo & client) const
{
	for (auto it = clients.begin(); it != clients.end();it++)
	{
		if ((*it)->get_socket().get_socket() == client.get_socket().get_socket()) return true;
	}
	return false;
}

Player & Game::otherPlayer(Player & player)
{
	for (auto client : clients) {
		if (&client->get_player() != &player) return client->get_player();
	}
	return player;
}

void Game::showState()
{
	for (auto & client : clients) {
		auto &player = client->get_player();
		if (!player.isWaiting() && hasState()) currentState->printOverview(*this, player);
		if (!player.isWaiting() && hasState()) currentState->printOptions(*this, player);
	}
	allPrompt();
}

void Game::start()
{
	notifyAllPlayers("Let the game begin, and may the best win.");

	// start with 2 coins and 4 buildings
	for (auto & client : clients) {
		auto &player = client->get_player();

		player.earnCoins(2);
		
		player.getHandBuildings().push_top_stack(move(buildingDeck.draw()));
		player.getHandBuildings().push_top_stack(move(buildingDeck.draw()));
		player.getHandBuildings().push_top_stack(move(buildingDeck.draw()));
		player.getHandBuildings().push_top_stack(move(buildingDeck.draw()));
	}

	int firstKing = RandomGenerator::getInstance().generate(0, static_cast<int>(clients.size())-1);
	
	auto &king = clients[firstKing]->get_player();
	king.setKing(true);

	notifyAllPlayers(king.get_name() + " is randomly chosen king!");

	startRound();
}

void Game::startRound()
{
	for (auto & client : clients) {
		client->get_player().getCharacterHand().clearAll();
	}
	characterHand.merge_stacks(false);
	characterHand.sortCharacters();

	for (auto it = characterHand.handBegin(); it != characterHand.handEnd(); it++) {
		(*it)->reset();
	}
	currentState = make_shared<ChooseCharacter>();

	for (auto & client : clients) {
		auto &player = client->get_player();
		player.resetRound();
		if (player.isKing()) {
			notifyAllPlayers();
			notifyAllPlayers("King " + player.get_name() + " starts this round!");
			player.notify();
		}
	}

}

void Game::endRound()
{	
	bool roundOver = false;

	int mostPoints = 0;
	vector<shared_ptr<ClientInfo>> mostPointsClients;

	notifyAllPlayers("");

	for (auto & client : clients) {
		auto &player = client->get_player();

		int points = player.countPoints();

		// (first) win points
		if (player.isFinished()) {
			roundOver = true;

			// Player won first
			if (&player == &(firstWon.lock())->get_player()) {
				points += 4;
			} // player won second
			else {
				points += 2;
			}
		}

		// put players with most points in a list
		if (points == mostPoints) mostPointsClients.push_back(client);
		else if (points > mostPoints) {
			mostPoints = points;
			mostPointsClients.clear();
			mostPointsClients.push_back(client);
		}

		notifyAllPlayers(player.get_name() + " currently has " + to_string(points) + " points");
	}

	if (roundOver) {

		if (mostPointsClients.size() == 1) {
			auto &player = mostPointsClients[0]->get_player();
			notifyAllPlayers("");
			notifyAllPlayers(player.get_name() + " has " + to_string(player.getBuiltBuildings().handAmount()) + " buildings and wins!");
		}
		else {
			mostPoints = 0;
			vector<shared_ptr<ClientInfo>> drawClients;

			for (auto & client : mostPointsClients) {
				auto &player = client->get_player();

				int points = player.countBuildingPoints();

				// put players with most points in a list
				if (points == mostPoints) drawClients.push_back(client);
				else if (points > mostPoints) {
					mostPoints = points;
					drawClients.clear();
					drawClients.push_back(client);
				}
			}

			if (drawClients.size() == 1) {
				auto &player = drawClients[0]->get_player();
				notifyAllPlayers("");
				notifyAllPlayers(player.get_name() + " has " + to_string(player.getBuiltBuildings().handAmount()) + " buildings and wins!");
			}
			else {
				notifyAllPlayers("It's a draw!");
			}
		}

		notifyAllPlayers("");
		notifyAllPlayers("Thanks for playing!");
		notifyAllPlayers("This game was made by Luuk Spierings and Jonathan Immink.");

		finished = true;
	}
	else {
		startRound();
	}
}

void Game::callNextCharacter()
{
	for (auto & client : clients) {
		if (client->get_player().isFinished() && !firstWon.lock()) {
			firstWon = client;
		}
	}
	
	if (currentState != nullptr && dynamic_cast<Character*>(currentState.get()) != nullptr) {
		characterHand.discard(move(characterHand.draw()));
	}

	if (characterHand.handBegin() != characterHand.handEnd()) {

		auto newCharacter = characterHand.top();
		currentState = newCharacter;

		for (auto & client : clients) {
			if (client->get_player().hasCharacter(newCharacter.get())) {

				auto &player = client->get_player();

				notifyAllPlayers("The " + newCharacter->getName() + " is called forward: " + player.get_name() + " is stepping forward.");
				player.notify();

				newCharacter->startCharacter(*this, player);

				player.setWaiting(false);
				otherPlayer(player).setWaiting(true);

				return;
			}
		}

		notifyAllPlayers("The " + newCharacter->getName() + " is called forward: only silence returns.");

		callNextCharacter();

	}
	else {
		// all characters have been called.
		notifyAllPlayers("All the characters have been called.");

		endRound();
	}

}

