#include "stdafx.h"
#include "CommandHandler.h"


void CommandHandler::handle(shared_ptr<ClientInfo> client, string command) {

	if (game.isFinished()) {
		game = Game{};
	}

	auto& socket = client->get_socket();
	auto& player = client->get_player();

	player.notify();

	if (command == "quit") {
		game.removeClient(*client);
		game.allPrompt();
		return;
	}

	player.notify("\u001B[2J");

	if (command == "help" || command == "h") {
		if (game.hasClient(*client)) {
			player.notify("Actions overview:");
			player.notify("- Take 2 coins OR take 2 cards and discarde 1 of them");
			player.notify("- Build a building from your hand");
			player.notify("- Character specific actions");
			player.notify();
			for (const auto& overzicht : game.getCharacterHand().getOverzicht()) {
				player.notify(overzicht);
			}
			player.prompt();
		}
		else {
			player.notify("-- Valid commands --");
			player.notify("join: Join a game.");
			player.notify("help: Shows this help page.");
			player.notify("quit: Quits the game / connection.");
			player.prompt();
		}	
	}
	else if (player.isWaiting() && game.hasClient(*client)) {
		player.notify("Please have patience, it is not your turn yet.");
		game.allPrompt();
	} 
	else if (game.hasState() && game.hasClient(*client)) {
		game.getCurrentState().processState(game, player, command);
		game.showState();
	}
	else {
		if (command == "join") {
			client->get_player().reset();
			game.addClient(client);
			game.showState();
		}
		else {
			player.notify("'" + command + "' is not a valid command.");
			player.prompt();
		}
	}

}

