#include "stdafx.h"
#include "Preacher.h"

void Preacher::startCharacter(Game & game, Player & player)
{
	Character::startCharacter(game, player);

	game.notifyAllPlayers(player.get_name() + " preaches for his buildings.");
	player.notify();

	player.preach();

}
