#pragma once

#include <vector>
#include <memory>

#include "Character.h"
#include "Game.h"
#include "Player.h"

class Condottiere : public Character {

public:
	Condottiere(int order) : Character(order) {
		color = CardColor::RED;
		name = "Condottiere";
	}

	void printOptions(Game& game, Player& player) override;
	void processState(Game& game, Player& player, string command) override;

private:

	bool choosingCards = false;

	void printChoosingOptions(Game & game, Player & player);
	void characterOptions(Game & game, Player & player) override;

};