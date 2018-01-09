#include "stdafx.h"
#include "DeckFactory.h"
#include "BuildingDeck.h"

unique_ptr<BuildingDeck> DeckFactory::loadBuildingDeck()
{
	BuildingDeck buildingDeck;
	std::ifstream stream("Bouwkaarten.csv");
	stream >> buildingDeck;
	stream.close();

	return std::make_unique<BuildingDeck>(buildingDeck);
}
