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
		player.notify("Please have patience, it is not your turn yet.");
	} 
	else if (game.hasState()) {

		game.getCurrentState().processState(game, player, command);

	}
	else {
		if (command == "join") {
			game.addClient(client);
		}
		else if (command == "help" || command == "h") {

			player.notify("-- Valid commands --");
			player.notify("join: Join a game.");
			player.notify("help: Shows this help page.");
			player.notify("quit: Quits the game / connection.");

		}
		else {
			player.notify("'" + command + "' is not a valid command.");
		}
	}

}

const string CommandHandler::getPrompt()
{
	return promptText;
}

void CommandHandler::prompt(Socket& client) {
	client << promptText;
};


