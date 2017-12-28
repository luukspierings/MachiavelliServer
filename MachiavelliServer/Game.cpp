#include "stdafx.h"
#include "Game.h"

void Game::addClient(shared_ptr<ClientInfo> client)
{
	for (auto& otherClient : clients) {
		otherClient->get_player().notify("Player '" + client->get_player().get_name() + "' joined the game.");
	}

	clients.push_back(client);
}

void Game::removeClient(ClientInfo & client)
{
	for (auto it = clients.begin(); it != clients.end();)
	{
		if ((*it)->get_socket().get_socket() == client.get_socket().get_socket()) {
			it = clients.erase(it);
		}
		else {
			++it;
		}
	}
}
