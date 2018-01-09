#pragma once

#include "Character.h"
#include "Player.h"
#include "Game.h"

class Preacher : public Character {

public:
	Preacher(int order) : Character(order) {
		color = CardColor::BLUE;
		name = "Preacher";
		description = "Stops the Condottiere from destroying his buildings and recieves income from blue buildings";
	}

	void startCharacter(Game& game, Player& player) override;

private:


};