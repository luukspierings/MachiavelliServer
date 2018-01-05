#include "stdafx.h"
#include "Merchant.h"

void Merchant::startCharacter(Game & game, Player & player)
{
	Character::startCharacter(game, player);

	game.notifyAllPlayers(player.get_name() + " earns 1 coin because he is the merchant.");
	player.notify();

	player.earnCoins(1);

}
