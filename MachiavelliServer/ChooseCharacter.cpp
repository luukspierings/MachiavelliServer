#include "stdafx.h"
#include "ChooseCharacter.h"


void ChooseCharacter::processState(Game & game, Player & player, string command)
{
	bool choseCharacter = false;
	int characterCount = 1;
	for (auto it = game.getCharacterHand().handBegin(); it != game.getCharacterHand().handEnd(); it++) {
		if ((*it)->isChosen()) continue;
		if (command == (*it)->getName() || command == to_string(characterCount)) {
			choseCharacter = true;

			if (choosingHand) {
				player.getCharacterHand().push_top_stack(*it);
			}
			(*it)->choose();

			break;
		}
		characterCount++;
	}
	
	if (allCharactersChosen(game, player)) {

		auto& otherPlayer = game.otherPlayer(player);

		otherPlayer.notify("All characters have been chosen, the next round is now starting.");
		player.notify("All characters have been chosen, the next round is now starting.");

		game.callNextCharacter();

	}
	else if (choseCharacter && choosingHand) {
		choosingHand = false;
	}
	else if (choseCharacter) {

		auto& newPlayer = game.otherPlayer(player);
		player.setWaiting(true);
		newPlayer.setWaiting(false);

		player.notify("It is now " + newPlayer.get_name() + "'s turn to pick and throw away characters.");

		newPlayer.notify(player.get_name() + " picked his characters, it is now your turn to pick and throw away characters.");

		choosingHand = true;
	}
	else {
		player.notify("'" + command + "' is not a character you can pick.");
	}
}

void ChooseCharacter::printOptions(Game & game, Player & player)
{

	player.notify("Characters in your hand:");

	for (auto it = player.getCharacterHand().handBegin(); it != player.getCharacterHand().handEnd(); it++) {
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
	for (auto it = game.getCharacterHand().handBegin(); it != game.getCharacterHand().handEnd(); it++) {
		if ((*it)->isChosen()) continue;
		player.notify("["+to_string(characterCount) + "] " + (*it)->getName());
		characterCount++;
	}


}

bool ChooseCharacter::allCharactersChosen(Game & game, Player & player)
{
	for (auto it = game.getCharacterHand().handBegin(); it != game.getCharacterHand().handEnd(); it++) {
		if (!(*it)->isChosen()) return false;
	}
	return true;
}
