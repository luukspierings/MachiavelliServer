#include "stdafx.h"
#include "Assassin.h"

void Assassin::printOptions(Game & game, Player & player)
{
	if (choosingCharacter) printKillingOptions(game, player);
	else Character::printOptions(game, player);
}

void Assassin::processState(Game & game, Player & player, string command)
{
	if (choosingCharacter && !performedCharacter) {

		if (command == "0") {
			choosingCharacter = false;
		}
		else {
			int characterCount = 1;
			for (auto it = game.getCharacterHand().handBegin(); it != game.getCharacterHand().handEnd(); it++) {
				if (command == (*it)->getName() || command == to_string(characterCount)) {

					if ((*it)->getName() == name) {
						player.notify("The " + name +" is not skilled enough to take his own life.");
						player.notify("Please pick someone else.");
						player.notify();
						return;
					}

					auto &otherPlayer = game.otherPlayer(player);
					if (otherPlayer.hasCharacter(it->get())) {
						for (auto character = otherPlayer.getCharacterHand().handBegin(); character != otherPlayer.getCharacterHand().handEnd(); character++) {
							if ((*character)->getName() == (*it)->getName()) (*character)->kill();
						}
					}

					otherPlayer.notify("The " + name + " silently killed the " + (*it)->getName());

					performedCharacter = true;
					choosingCharacter = false;
					return;
				}
				characterCount++;
			}

			player.notify("'" + command + "' is not a character you can kill.");
			player.notify();
		}
	}
	else {
		if (command == "6") {
			choosingCharacter = true;
		} else {
			Character::processState(game, player, command);
		}
	}

}

void Assassin::printKillingOptions(Game & game, Player & player)
{
	player.notify("Pick a character to kill:");
	player.notify("[0] Don't kill anyone yet");
	int characterCount = 1;
	for (auto it = game.getCharacterHand().handBegin(); it != game.getCharacterHand().handEnd(); it++) {
		player.notify("[" + to_string(characterCount) + "] " + (*it)->getName());
		characterCount++;
	}
}

void Assassin::characterOptions(Game & game, Player & player)
{
	player.notify("[6] Choose a character to kill");
}
