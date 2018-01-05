#pragma once

#include "Character.h"
#include "Player.h"
#include "Game.h"

class Builder : public Character {

public:
	Builder() {
		name = "Builder";
	}

	void startCharacter(Game& game, Player& player) override;


private:


};