#include "stdafx.h"
#include "CommandHandler.h"


void CommandHandler::handle(shared_ptr<ClientInfo> client, string command) {

	auto& socket = client->get_socket();
	auto& player = client->get_player();

	player.notify();

	if (command == "quit") {
		game.removeClient(*client);
		game.allPrompt();
		return;
	}

	player.notify("\u001B[2J");

	if (player.isWaiting()) {
		player.notify("Please have patience, it is not your turn yet.");
		game.allPrompt();
	} 
	else if (game.hasState()) {

		game.getCurrentState().processState(game, player, command);
		if (!player.isWaiting()) game.getCurrentState().printOverview(game, player);
		if (!player.isWaiting()) game.getCurrentState().printOptions(game, player);
		
		game.allPrompt();
	}
	else {
		if (command == "join") {
			game.addClient(client);

			game.allPrompt();
		}
		else if (command == "help" || command == "h") {

			player.notify("-- Valid commands --");
			player.notify("join: Join a game.");
			player.notify("help: Shows this help page.");
			player.notify("quit: Quits the game / connection.");

			player.prompt();
		}
		else {
			player.notify("'" + command + "' is not a valid command.");

			player.prompt();
		}
	}

}

