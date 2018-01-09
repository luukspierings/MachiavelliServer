#pragma once

#include <memory>

class BuildingDeck;

using namespace std;

class DeckFactory {


public:
	unique_ptr<BuildingDeck> loadBuildingDeck();

private:

};


