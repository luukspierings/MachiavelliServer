#pragma once

#include "Character.h"
#include "Player.h"
#include "Game.h"

class King : public Character {

public:
	King(int order) : Character(order) {
		color = CardColor::YELLOW;
		name = "King";
		description = "Let's the player start the round and recieves income from yellow buildings";
	}

	void startCharacter(Game& game, Player& player) override;


private:


};