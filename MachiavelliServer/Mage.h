#pragma once

#include <memory>
#include <vector>

#include "Character.h"
#include "Player.h"
#include "Game.h"
#include "BuildingHand.h"

class Mage : public Character {

public:
	Mage(int order) : Character(order) {
		name = "Mage";
		description = "Could trade building cards";
	}

	void printOptions(Game& game, Player& player) override;
	void processState(Game& game, Player& player, string command) override;

private:

	BuildingHand chosenSwaps;
	bool choosingCards = false;

	void printChoosingOptions(Game & game, Player & player);
	void characterOptions(Game & game, Player & player) override;
};