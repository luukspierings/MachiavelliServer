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
			for (auto & order : game.getCharacterOrder()) {
				if (command == order || command == to_string(characterCount)) {

					if (order == name) {
						player.notify("The assassin is not skilled enough to take his own life.");
						player.notify("Please pick someone else.");
						return;
					}

					auto &otherPlayer = game.otherPlayer(player);
					if (otherPlayer.hasCharacter(order)) {
						for (auto character = otherPlayer.charactersBegin(); character != otherPlayer.charactersEnd(); character++) {
							if ((*character)->getName() == order) (*character)->kill();
						}
					}

					otherPlayer.notify("The assassin silently killed the " + order);

					performedCharacter = true;
					choosingCharacter = false;
					return;
				}
				characterCount++;
			}

			player.notify("'" + command + "' is not a character you can kill.");
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
	for (auto & order : game.getCharacterOrder()) {
		player.notify("[" + to_string(characterCount) + "] " + order);
		characterCount++;
	}
}

void Assassin::characterOptions(Game & game, Player & player)
{
	player.notify("[6] Choose a character to kill");
}
