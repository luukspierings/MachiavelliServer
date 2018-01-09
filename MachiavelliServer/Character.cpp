#include "stdafx.h"
#include "Character.h"
#include "Game.h"
#include "Player.h"

void Character::startCharacter(Game & game, Player & player)
{
	if (stolen) {
		auto &otherPlayer = game.otherPlayer(player);
		int stolenCoins = player.stealCoins();
		otherPlayer.earnCoins(stolenCoins);
		otherPlayer.notify("You stole " + to_string(stolenCoins) + " coins from " + player.get_name());

		player.notify(otherPlayer.get_name() + " stole " + to_string(stolenCoins) + " coins from you!");
		player.notify();
	}

	int earning = 0;
	for (auto& it = player.getBuiltBuildings().handBegin(); it != player.getBuiltBuildings().handEnd(); it++) {
		if (it->getColor() == color) earning++;
	}
	player.earnCoins(earning);
	if (earning > 0) game.notifyAllPlayers(player.get_name() + " earned " + to_string(earning) + " coins from his buildings.");
}

void Character::printOptions(Game & game, Player & player)
{
	if (choosingBuild) buildOptions(game, player);
	else if (choosingBuildingCard) chooseBuildingOptions(game, player);
	else defaultOptions(game, player);
}

void Character::processState(Game & game, Player & player, string command)
{
	if (choosingBuild) {

		if (command == "0") {
			choosingBuild = false;
		}
		else {
			int buildingCount = 1;
			for (auto it = player.getHandBuildings().handBegin(); it != player.getHandBuildings().handEnd(); it++) {
				if (command == it->getName() || command == to_string(buildingCount)) {

					if (it->getCost() > player.getCoins()) {
						player.notify("You don't have enough coins to buy this building!");
						player.notify();
					}
					else {
						game.notifyAllPlayers(player.get_name() + " builds the building: " + it->getPrint());
						player.buyBuilding(it->getName());
						buildingsBuilt++;
						if(buildingsBuilt >= maxBuilding) choosingBuild = false;
					}
					return;
				}
				buildingCount++;
			}

			player.notify("'" + command + "' is not a building you can build.");
		}

	}
	else if (choosingBuildingCard) {

		bool choseCard = false;
		int buildingCount = 1;
		for (auto it = buildingCards.begin(); it != buildingCards.end();) {
			if (command == it->getName() || command == to_string(buildingCount)) {
				player.getHandBuildings().push_top_stack(move(*it));
				it = buildingCards.erase(it);
				choseCard = true;
			}
			else {
				it++;
			}
			buildingCount++;
		}

		if (choseCard) {
			for (auto it = buildingCards.begin(); it != buildingCards.end();) {
				game.getBuildingDeck().discard(move(*it));
				it = buildingCards.erase(it);
			}
			choosingBuildingCard = false;
			performedDefault = true;
			return;
		}

		player.notify("'" + command + "' is not a building you can choose from.");
	}
	else {
		if (command == "1") {
			player.setWaiting(true);
			game.otherPlayer(player).setWaiting(true);
			game.notifyAllPlayers(player.get_name() + " ends its turn.");
			game.callNextCharacter();
			return;
		}
		else if (command == "2") {

			auto &otherPlayer = game.otherPlayer(player);

			player.notify(otherPlayer.get_name() + "'s coins: " + to_string(otherPlayer.getCoins()));
			player.notify(otherPlayer.get_name() + "'s buildings in hand: " + to_string(otherPlayer.getHandBuildings().handAmount()));
			player.notify(otherPlayer.get_name() + "'s buildings built:");
			for (auto it = otherPlayer.getBuiltBuildings().handBegin(); it != otherPlayer.getBuiltBuildings().handEnd(); it++) {
				player.notify("- " + it->getPrint());
			}
			player.notify();

		}
		else if (!performedDefault && command == "3") {
			player.earnCoins(2);
			performedDefault = true;
		}
		else if (!performedDefault && command == "4") {
			buildingCards.push_back(move(game.getBuildingDeck().draw()));
			buildingCards.push_back(move(game.getBuildingDeck().draw()));
			choosingBuildingCard = true;
		}
		else if (buildingsBuilt < maxBuilding && command == "5") {
			choosingBuild = true;
		}
		else {
			player.notify("'" + command + "' is not an option.");
		}
	}

}

void Character::reset()
{
	chosen = false;
	dead = false;
	stolen = false;
}

void Character::printOverview(Game & game, Player & player)
{
	player.notify("Amount of coins: " + to_string(player.getCoins()));
	player.notify("Current character: " + getName());
	player.notify();

	player.notify("Buildings built:");
	for (auto it = player.getBuiltBuildings().handBegin(); it != player.getBuiltBuildings().handEnd(); it++) {
		player.notify("- " + it->getPrint());
	}

	player.notify();

	player.notify("Buildings in hand:");
	for (auto it = player.getHandBuildings().handBegin(); it != player.getHandBuildings().handEnd(); it++) {
		player.notify("- " + it->getPrint());
	}

	if (player.getCharacterHand().handBegin() != player.getCharacterHand().handEnd()) {
		player.notify();
		player.notify("Characters left:");
		for (auto it = player.getCharacterHand().handBegin(); it != player.getCharacterHand().handEnd(); it++) {
			player.notify("- " + (*it)->getName() + ((*it)->isDead()? " (assassinated)" : ""));
		}
	}
	player.notify();
}

void Character::defaultOptions(Game & game, Player & player)
{
	player.notify("Choose an option:");
	player.notify("[1] End turn");
	player.notify("[2] Look at enemy's buildings and gold");
	if (!performedDefault) {
		player.notify("[3] Take 2 coins, or:");
		player.notify("[4] Take 2 building cards and choose 1");
	}
	if (buildingsBuilt < maxBuilding) player.notify("[5] Build a building from your hand");
	if (!performedCharacter) characterOptions(game, player);
}

void Character::buildOptions(Game & game, Player & player)
{
	player.notify("Choose a building to build:");
	player.notify("[0] Don't build for now");
	int buildingCount = 1;
	for (auto it = player.getHandBuildings().handBegin(); it != player.getHandBuildings().handEnd(); it++) {
		player.notify("[" + to_string(buildingCount) + "] " + to_string(it->getCost()) + " coins | " + it->getPrint());
		buildingCount++;
	}
}

void Character::chooseBuildingOptions(Game & game, Player & player)
{
	player.notify("Choose the building to keep, the other discards:");
	int buildingCount = 1;
	for (auto& building : buildingCards) {
		player.notify("["+ to_string(buildingCount)+"] " + building.getPrint());
		buildingCount++;
	}
}
