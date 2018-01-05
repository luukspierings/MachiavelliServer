#include "stdafx.h"
#include "Builder.h"

void Builder::startCharacter(Game & game, Player & player)
{
	Character::startCharacter(game, player);
	maxBuilding = 3;

	player.putBuilding(move(game.getBuilding()));
	player.putBuilding(move(game.getBuilding()));
}
