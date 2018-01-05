#include "stdafx.h"
#include "Robber.h"

void Robber::printOptions(Game & game, Player & player)
{
	if (choosingCharacter) printStealingOptions(game, player);
	else Character::printOptions(game, player);
}

void Robber::processState(Game & game, Player & player, string command)
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
						player.notify("The " + name +" can't steal from himself, Mrs. " + name + " already does that to him.");
						player.notify("Please pick someone else.");
						player.notify();
						return;
					}

					auto &otherPlayer = game.otherPlayer(player);
					if (otherPlayer.hasCharacter(order)) {
						for (auto character = otherPlayer.charactersBegin(); character != otherPlayer.charactersEnd(); character++) {
							if ((*character)->getName() == order) (*character)->steal();
						}
					}

					otherPlayer.notify("The "+ name +" stole from the " + order);

					performedCharacter = true;
					choosingCharacter = false;
					return;
				}
				characterCount++;
			}

			player.notify("'" + command + "' is not a character you can steal from.");
			player.notify();
		}
	}
	else {
		if (command == "6") {
			choosingCharacter = true;
		}
		else {
			Character::processState(game, player, command);
		}
	}

}

void Robber::printStealingOptions(Game & game, Player & player)
{
	player.notify("Pick a character to steal from:");
	player.notify("[0] Don't steal anyone yet");
	int characterCount = 1;
	for (auto & order : game.getCharacterOrder()) {
		player.notify("[" + to_string(characterCount) + "] " + order);
		characterCount++;
	}
}

void Robber::characterOptions(Game & game, Player & player)
{
	player.notify("[6] Choose a character to steal from");
}
