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

			if (chosenSwaps.handAmount() > 0) {

				for (auto it = chosenSwaps.handBegin(); it != chosenSwaps.handEnd(); it = chosenSwaps.handBegin()) {
					game.getBuildingDeck().discard(move(chosenSwaps.draw()));
					player.getHandBuildings().push_top_stack(move(game.getBuildingDeck().draw()));
				}

				performedCharacter = true;
			}
		}
		else {
			int cardCount = 1;
			for (auto it = player.getHandBuildings().handBegin(); it != player.getHandBuildings().handEnd(); it++) {
				if (command == it->getName() || command == to_string(cardCount)) {
					chosenSwaps.push_top_stack(player.getHandBuildings().handPull(it));
					return;
				}
				cardCount++;
			}
			for (auto it = chosenSwaps.handBegin(); it != chosenSwaps.handEnd(); it++) {
				if (command == it->getName() || command == to_string(cardCount)) {
					player.getHandBuildings().push_top_stack(move(chosenSwaps.handPull(it)));
					return;
				}				
				cardCount++;
			}

			player.notify("'" + command + "' is not a card you can choose.");
		}
	}
	else {
		if (command == "6") {

			BuildingHand buffer;

			auto &otherPlayer = game.otherPlayer(player);

			for (auto it = player.getHandBuildings().handBegin(); it != player.getHandBuildings().handEnd(); it = player.getHandBuildings().handBegin()) {
				buffer.push_top_stack(player.getHandBuildings().handPull(it));
			}
			for (auto it = otherPlayer.getHandBuildings().handBegin(); it != otherPlayer.getHandBuildings().handEnd(); it = otherPlayer.getHandBuildings().handBegin()) {
				player.getHandBuildings().push_top_stack(otherPlayer.getHandBuildings().handPull(it));
			}
			for (auto it = buffer.handBegin(); it != buffer.handEnd(); it = buffer.handBegin()) {
				otherPlayer.getHandBuildings().push_top_stack(buffer.handPull(it));
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
	for (auto it = player.getHandBuildings().handBegin(); it != player.getHandBuildings().handEnd(); it++) {
		player.notify("[" + to_string(cardCount) + "] " + it->getPrint());
		cardCount++;
	}
	if (chosenSwaps.handAmount() > 0) {
		player.notify();
		player.notify("Cards swapping (choose one to undo swap):");
		for (auto it = chosenSwaps.handBegin(); it != chosenSwaps.handEnd(); it++) {
			player.notify("[" + to_string(cardCount) + "] " + it->getPrint());
			cardCount++;
		}
	}
}

void Mage::characterOptions(Game & game, Player & player)
{
	player.notify("[6] Swap your building cards with enemy's building cards");
	player.notify("[7] Swap a number of building cards with the main stack");
}
