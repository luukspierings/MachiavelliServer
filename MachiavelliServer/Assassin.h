#pragma once

#include "Character.h"
#include "Game.h"
#include "Player.h"

class Assassin : public Character{

public:
	Assassin(int order): Character(order) {
		name = "Assassin";
		description = "Kills another character";
	}


	void printOptions(Game& game, Player& player) override;
	void processState(Game& game, Player& player, string command) override;


private:

	bool choosingCharacter = false;

	void printKillingOptions(Game & game, Player & player);
	void characterOptions(Game & game, Player & player) override;


};