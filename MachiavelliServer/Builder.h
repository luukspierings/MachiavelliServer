#pragma once

#include "Character.h"
#include "Player.h"
#include "Game.h"

class Builder : public Character {

public:
	Builder(int order) : Character(order) {
		name = "Builder";
		description = "Pulls 2 extra cards and is able to build 3 buildings";
	}

	void startCharacter(Game& game, Player& player) override;


private:


};