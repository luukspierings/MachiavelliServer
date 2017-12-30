#include "stdafx.h"
#include "ChooseCharacter.h"


void ChooseCharacter::processState(Game & game, Player & player, string command)
{
	bool choseCharacter = false;
	int characterCount = 1;
	for (vector<unique_ptr<Character>>::iterator it = game.charactersBegin(); it != game.charactersEnd(); it++) {
		if (command == (*it)->getName() || command == to_string(characterCount)) {
			choseCharacter = true;

			if (choosingHand) {
				player.putCharacter(std::move(*it));
				game.removeCharacter(it);
			}
			else {
				game.removeCharacter(it);
			}

			break;
		}
		characterCount++;
	}
	
	if (game.charactersBegin() == game.charactersEnd()) {

		auto& otherPlayer = game.otherPlayer(player);

		otherPlayer.notify("\r\nAll characters have been chosen, the next round is now starting.");
		player.notify("All characters have been chosen, the next round is now starting.");

		game.callNextCharacter();

	}
	else if (choseCharacter && choosingHand) {
		choosingHand = false;
		printOptions(game, player);
	}
	else if (choseCharacter) {

		auto& newPlayer = game.otherPlayer(player);
		player.setWaiting(true);
		newPlayer.setWaiting(false);

		player.notify("It is now " + newPlayer.get_name() + "'s turn to pick and throw away characters.");

		newPlayer.notify("\r\n" + player.get_name() + " picked his characters, it is now your turn to pick and throw away characters.");

		choosingHand = true;
		printOptions(game, newPlayer);

	}
	else {
		player.notify("'" + command + "' is not a character you can pick.");
		printOptions(game, player);
	}
}

void ChooseCharacter::printOptions(Game & game, Player & player)
{

	player.notify("Characters in your hand:");

	for (auto it = player.charactersBegin(); it != player.charactersEnd(); it++) {
		player.notify("- " + (*it)->getName());
	}

	player.notify("");

	if (choosingHand) {
		player.notify("Please choose a character to add to your hand:");
	}
	else {
		player.notify("Please choose a character to discard from the deck:");
	}

	int characterCount = 1;
	for (auto it = game.charactersBegin(); it != game.charactersEnd(); it++) {
		player.notify("["+to_string(characterCount) + "] " + (*it)->getName());
		characterCount++;
	}


}
