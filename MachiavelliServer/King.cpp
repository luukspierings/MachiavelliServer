#include "stdafx.h"
#include "King.h"

void King::startCharacter(Game & game, Player & player)
{
	Character::startCharacter(game, player);

	game.notifyAllPlayers(player.get_name() + " is now king!");
	player.notify();

}
