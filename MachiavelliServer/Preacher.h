#pragma once

#include "Character.h"
#include "Player.h"
#include "Game.h"

class Preacher : public Character {

public:
	Preacher() {
		color = CardColor::BLUE;
		name = "Preacher";
	}

	void startCharacter(Game& game, Player& player) override;

private:


};