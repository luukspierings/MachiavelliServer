#include "stdafx.h"
#include "Condottiere.h"

void Condottiere::printOptions(Game & game, Player & player)
{
	if (choosingCards) printChoosingOptions(game, player);
	else Character::printOptions(game, player);
}

void Condottiere::processState(Game & game, Player & player, string command)
{
	if (choosingCards && !performedCharacter) {

		if (command == "0") {
			choosingCards = false;
		}
		else {
			auto &otherPlayer = game.otherPlayer(player);
			int cardCount = 1;

			for (auto it = otherPlayer.stackBuildingsBegin(); it != otherPlayer.stackBuildingsEnd(); it++) {
				if (command == (*it)->getName() || command == to_string(cardCount)) {

					if (player.getCoins() < (*it)->getDestroyCost()) {
						player.notify("You don't have enough coins to destroy this building!");
						player.notify();
					}
					else {
						player.loseCoins((*it)->getDestroyCost());

						game.notifyAllPlayers(player.get_name() + " destroys " + otherPlayer.get_name() + "'s building: " + (*it)->getPrint());

						game.returnBuilding(otherPlayer.destroyBuilding((*it)->getName()));

						performedCharacter = true;
						choosingCards = false;
						return;
					}
				}
				cardCount++;
			}

			player.notify("'" + command + "' is not a card you can choose.");
		}
	}
	else {
		if (command == "6" && !game.otherPlayer(player).isFinished()) {
			choosingCards = true;
		}
		else {
			Character::processState(game, player, command);
		}
	}

}

void Condottiere::printChoosingOptions(Game & game, Player & player)
{
	player.notify("Pick a building to destroy:");
	player.notify("[0] Don't destroy anything for now");

	auto &otherPlayer = game.otherPlayer(player);

	int cardCount = 1;
	for (auto it = otherPlayer.stackBuildingsBegin(); it != otherPlayer.stackBuildingsEnd(); it++) {
		player.notify("[" + to_string(cardCount) + "] " + to_string((*it)->getDestroyCost()) + " coins | " + (*it)->getPrint());
		cardCount++;
	}
}

void Condottiere::characterOptions(Game & game, Player & player)
{
	if (game.otherPlayer(player).isFinished()) player.notify("[-] Enemy has 8 or more buildings, so you can't destroy any more buildings");
	else player.notify("[6] Destroy an enemy's building");
}



