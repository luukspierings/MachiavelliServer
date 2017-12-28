#include "stdafx.h"
#include "CommandHandler.h"


void CommandHandler::handle(shared_ptr<ClientInfo> client, string command) {

	auto& socket = client->get_socket();
	auto& player = client->get_player();


	if (command == "quit") {

		game.removeClient(*client);

		return;
	}


	if (player.isWaiting()) {
		socket << "Please have patience, it is not your turn yet.\r\n";
	} 
	else {
		if (command == "join") {

			game.addClient(client);

			socket << "You successfully joined a game.\r\n";
			
			int clientAmount = game.getClientsAmount();
			socket << "The game currently consists of you and " << clientAmount - 1 << " other players.\r\n";
			socket << "Please wait for the game to start...\r\n";

			player.setWaiting(true);

		}
		else if (command == "help" || command == "h") {
			socket << "-- Valid commands --\r\n";
			socket << "join: Join a game.\r\n";
			socket << "help: Shows this help page\r\n";
			socket << "quit: Quits the game / connection\r\n";
		}
		else {
			socket << "'" << command << "' is not a valid command.\r\n";
		}
	}

	prompt(socket);
}

const string CommandHandler::getPrompt()
{
	return promptText;
}

void CommandHandler::prompt(Socket& client) {
	client << promptText;
};


