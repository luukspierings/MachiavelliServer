#include "stdafx.h"
#include "DeckFactory.h"
#include "BuildingDeck.h"
#include "CharacterHand.h"

void DeckFactory::loadBuildingDeck(BuildingDeck& deck)
{
	try
	{
		std::ifstream stream("Bouwkaarten.csv");
		stream >> deck;
		stream.close();
	}
	catch(...)
	{
		throw std::runtime_error(std::string("Error while loading Bouwkaarten.csv"));
	}
}

void DeckFactory::loadCharacterHand(CharacterHand& hand)
{
	try
	{
		std::ifstream stream("karakterkaarten.csv");
		stream >> hand;
		stream.close();
	}
	catch (...)
	{
		throw std::runtime_error(std::string("Error while loading karakterkaarten.csv"));
	}
}
