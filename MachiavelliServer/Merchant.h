#pragma once

#include "Character.h"
#include "Player.h"
#include "Game.h"

class Merchant : public Character {

public:
	Merchant() {
		color = CardColor::GREEN;
		name = "Merchant";
	}

	void startCharacter(Game& game, Player& player) override;

private:


};