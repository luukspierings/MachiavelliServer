#include "stdafx.h"
#include "DeckFactory.h"
#include "BuildingDeck.h"
#include "CharacterHand.h"

void DeckFactory::loadBuildingDeck(BuildingDeck& deck)
{
	std::ifstream stream("Bouwkaarten.csv");
	stream >> deck;
	stream.close();
}

void DeckFactory::loadCharacterHand(CharacterHand& hand)
{
	std::ifstream stream("karakterkaarten.csv");
	stream >> hand;
	stream.close();
}
