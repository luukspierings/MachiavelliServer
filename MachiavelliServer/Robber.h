#pragma once

#include "Character.h"
#include "Player.h"
#include "Game.h"

class Robber : public Character {

public:
	Robber(int order) : Character(order) {
		name = "Robber";
	}

	void printOptions(Game& game, Player& player) override;
	void processState(Game& game, Player& player, string command) override;

private:

	bool choosingCharacter = false;

	void printStealingOptions(Game & game, Player & player);
	void characterOptions(Game & game, Player & player) override;

};