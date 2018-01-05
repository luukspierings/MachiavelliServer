#include "stdafx.h"
#include "Mage.h"

void Mage::printOptions(Game & game, Player & player)
{
	if (choosingCards) printChoosingOptions(game, player);
	else Character::printOptions(game, player);
}

void Mage::processState(Game & game, Player & player, string command)
{
	if (choosingCards && !performedCharacter) {

		if (command == "0") {
			choosingCards = false;			

			if (chosenSwaps.size() > 0) {

				for (auto it = chosenSwaps.begin(); it != chosenSwaps.end();) {
					game.returnBuilding(move(*it));
					it = chosenSwaps.erase(it);
					player.putBuilding(game.getBuilding());
				}

				performedCharacter = true;
			}
		}
		else {
			int cardCount = 1;
			for (auto it = player.handBuildingsBegin(); it != player.handBuildingsEnd();) {
				if (command == (*it)->getName() || command == to_string(cardCount)) {
					chosenSwaps.push_back(player.pullBuilding((*it)->getName()));
					return;
				}
				else it++;

				cardCount++;
			}
			for (auto it = chosenSwaps.begin(); it != chosenSwaps.end();) {
				if (command == (*it)->getName() || command == to_string(cardCount)) {
					player.putBuilding(move(*it));
					it = chosenSwaps.erase(it);
					return;
				}
				else it++;
				
				cardCount++;
			}

			player.notify("'" + command + "' is not a card you can choose.");
		}
	}
	else {
		if (command == "6") {

			vector<unique_ptr<Building>> buffer;

			auto &otherPlayer = game.otherPlayer(player);

			for (auto it = player.handBuildingsBegin(); it != player.handBuildingsEnd();) {
				buffer.push_back(player.pullBuilding((*it)->getName()));
				it = player.handBuildingsBegin();
			}
			for (auto it = otherPlayer.handBuildingsBegin(); it != otherPlayer.handBuildingsEnd();) {
				player.putBuilding(otherPlayer.pullBuilding((*it)->getName()));
				it = otherPlayer.handBuildingsBegin();
			}
			for (auto it = buffer.begin(); it != buffer.end();) {
				otherPlayer.putBuilding(move(*it));
				it = buffer.erase(it);
			}

			otherPlayer.notify(otherPlayer.get_name() + " swaps his building cards with your cards.");

			performedCharacter = true;
		}
		else if (command == "7") {
			choosingCards = true;
		}
		else {
			Character::processState(game, player, command);
		}
	}

}

void Mage::printChoosingOptions(Game & game, Player & player)
{
	player.notify("Pick cards to swap with the main stack:");
	player.notify("[0] Done choosing");
	int cardCount = 1;
	for (auto it = player.handBuildingsBegin(); it != player.handBuildingsEnd(); it++) {
		player.notify("[" + to_string(cardCount) + "] " + (*it)->getPrint());
		cardCount++;
	}
	if (chosenSwaps.size() > 0) {
		player.notify();
		player.notify("Cards swapping (choose one to undo swap):");
		for (auto & card : chosenSwaps) {
			player.notify("[" + to_string(cardCount) + "] " + card->getPrint());
			cardCount++;
		}
	}
}

void Mage::characterOptions(Game & game, Player & player)
{
	player.notify("[6] Swap your building cards with enemy's building cards");
	player.notify("[7] Swap a number of building cards with the main stack");
}
