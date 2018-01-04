#include "stdafx.h"
#include "Game.h"

void Game::addClient(shared_ptr<ClientInfo> client)
{
	auto &player = client->get_player();

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
}

Player & Game::otherPlayer(Player & player)
{
	for (auto client : clients) {
		if (&client->get_player() != &player) return client->get_player();
	}
	return player;
}

void Game::shuffleBuildings()
{
	std::shuffle(buildings.begin(), buildings.end(), std::default_random_engine{});
	std::shuffle(buildings.begin(), buildings.end(), std::default_random_engine{});
	std::shuffle(buildings.begin(), buildings.end(), std::default_random_engine{});
}

unique_ptr<Building> Game::getBuilding()
{
	unique_ptr<Building> buf;

	if (buildings.begin() == buildings.end()) {
		swap(buildings, returnedBuildings);
		shuffleBuildings();
	}
	buf = move(buildings.back());
	buildings.pop_back();

	return buf;
}

void Game::returnBuilding(unique_ptr<Building> building)
{
	returnedBuildings.push_back(move(building));
}


void Game::start()
{
	notifyAllPlayers("Let the game begin, and may the best win.");

	// start with 2 coins and 3 buildings
	for (auto & client : clients) {
		auto &player = client->get_player();

		player.earnCoins(2);
		
		player.putBuilding(move(getBuilding()));
		player.putBuilding(move(getBuilding()));
		player.putBuilding(move(getBuilding()));
	}

	int firstKing = RandomGenerator::getInstance().generate(0, static_cast<int>(clients.size())-1);
	
	auto &king = clients[firstKing]->get_player();
	king.setKing(true);

	notifyAllPlayers(king.get_name() + " is randomly chosen king!");

	startRound();
}

void Game::startRound()
{
	resetCharacters();
	currentState = make_unique<ChooseCharacter>();

	for (auto & client : clients) {
		auto &player = client->get_player();
		player.resetRound();
		if (player.isKing()) {
			notifyAllPlayers();
			notifyAllPlayers("King " + player.get_name() + " starts this round!");
			currentState->printOptions(*this, player);
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
			notifyAllPlayers(player.get_name() + " has " + to_string(player.stackBuildingsAmount()) + " buildings and wins!");
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
				notifyAllPlayers(player.get_name() + " has " + to_string(player.stackBuildingsAmount()) + " buildings and wins!");

			}
			else {

				notifyAllPlayers("It's a draw!");

			}

		}

		notifyAllPlayers("");
		notifyAllPlayers("Thanks for playing!");
		notifyAllPlayers("This game was made by Luuk Spierings and Jonathan Immink.");
	}
	else {

		startRound();
	}
}

void Game::callNextCharacter(string lastCharacter)
{
	for (auto & client : clients) {
		if (client->get_player().isFinished() && !firstWon.lock()) {
			firstWon = client;
		}
	}

	string newCharacter = "";
	if (lastCharacter == "") {
		if (characterOrder.size() > 0) newCharacter = characterOrder[0];
	}
	else {
		bool lastPassed = false;
		for (auto character : characterOrder) {
			if (lastPassed) {
				newCharacter = character;
				break;
			}
			else if (lastCharacter == character) lastPassed = true;
		}
	}

	if (newCharacter != "") {

		for (auto & client : clients) {
			if (client->get_player().hasCharacter(newCharacter)) {

				auto &player = client->get_player();

				notifyAllPlayers("The " + newCharacter + " is called forward: " + player.get_name() + " is stepping forward.");

				currentState = player.pullCharacter(newCharacter);
				currentState->printOverview(*this, player);
				currentState->printOptions(*this, player);

				player.setWaiting(false);
				otherPlayer(player).setWaiting(true);

				return;
			}
		}

		notifyAllPlayers("The " + newCharacter + " is called forward: only silence returns.");

		callNextCharacter(newCharacter);

	}
	else {
		// all characters have been called.
		notifyAllPlayers("All the characters have been called.");

		endRound();
	}

}

void Game::resetCharacters()
{
	characters = characterFactory.getCharacters();

	characterOrder.clear();
	for (auto & c : characters) {
		characterOrder.push_back(c->getName());
	}

}
