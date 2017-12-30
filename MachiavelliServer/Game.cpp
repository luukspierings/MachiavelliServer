#include "stdafx.h"
#include "Game.h"

void Game::addClient(shared_ptr<ClientInfo> client)
{
	auto &player = client->get_player();

	notifyAllPlayers("\r\nPlayer '" + player.get_name() + "' has joined the game.");
	
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
	for (auto& client : clients) {
		if (&client->get_player() != &player) return client->get_player();
	}
}

void Game::shuffleBuildings()
{
	std::shuffle(buildings.begin(), buildings.end(), std::default_random_engine{});
	std::shuffle(buildings.begin(), buildings.end(), std::default_random_engine{});
	std::shuffle(buildings.begin(), buildings.end(), std::default_random_engine{});
}

void Game::setCharacterOrder()
{
	characterOrder.clear();

	for (auto & c : characterFactory.getCharacters()) {
		characterOrder.push_back(c->getName());
	}

}

void Game::start()
{
	notifyAllPlayers("Let the game begin, and may the best win.");

	int firstKing = RandomGenerator::getInstance().generate(0, static_cast<int>(clients.size())-1);
	
	auto &king = clients[firstKing]->get_player();
	king.setKing(true);
	king.notify("\r\nYou are declared king!");

	currentState = make_unique<ChooseCharacter>();

	currentState->printOptions(*this, king);
	king.setWaiting(false);
}

void Game::callNextCharacter(string lastCharacter)
{
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

				notifyAllPlayers("The " + newCharacter + " is called forward: " + player.get_name() + " has the character.");

				currentState = player.pullCharacter(newCharacter);
				currentState->printOptions(*this, player);

				player.setWaiting(false);
				otherPlayer(player).setWaiting(true);

				return;
			}
		}

		notifyAllPlayers("The " + newCharacter + " is called forward: nobody has the character.");

		callNextCharacter(newCharacter);

	}
	else {
		// Done all characters

		notifyAllPlayers("All the characters have been called. The round begins again soon.");

	}

}
