#include "stdafx.h"
#include "Game.h"

void Game::addClient(shared_ptr<ClientInfo> client)
{
	notifyAllPlayers("Player '" + client->get_player().get_name() + "' has joined the game.");

	clients.push_back(client);
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
