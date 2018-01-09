#include "stdafx.h"
#include "Builder.h"

void Builder::startCharacter(Game & game, Player & player)
{
	Character::startCharacter(game, player);
	maxBuilding = 3;

	player.getHandBuildings().push_top_stack(move(game.getBuildingDeck().draw()));
	player.getHandBuildings().push_top_stack(move(game.getBuildingDeck().draw()));
}
