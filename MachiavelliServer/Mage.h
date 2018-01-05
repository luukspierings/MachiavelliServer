#pragma once

#include <memory>
#include <vector>

#include "Character.h"
#include "Player.h"
#include "Game.h"

class Mage : public Character {

public:
	Mage() {
		name = "Mage";
	}

	void printOptions(Game& game, Player& player) override;
	void processState(Game& game, Player& player, string command) override;

private:

	vector<unique_ptr<Building>> chosenSwaps{};
	bool choosingCards = false;

	void printChoosingOptions(Game & game, Player & player);
	void characterOptions(Game & game, Player & player) override;
};