#pragma once

#include "Character.h"
#include "Player.h"
#include "Game.h"

class King : public Character {

public:
	King() {
		color = CardColor::YELLOW;
		name = "King";
	}

	void startCharacter(Game& game, Player& player) override;


private:


};