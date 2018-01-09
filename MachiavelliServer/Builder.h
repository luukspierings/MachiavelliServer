#pragma once

#include "Character.h"
#include "Player.h"
#include "Game.h"

class Builder : public Character {

public:
	Builder(int order) : Character(order) {
		name = "Builder";
	}

	void startCharacter(Game& game, Player& player) override;


private:


};