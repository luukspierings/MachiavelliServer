#pragma once

#include <memory>
#include <stdexcept>

class BuildingDeck;
class CharacterHand;

using namespace std;

class DeckFactory {

public:
	void loadBuildingDeck(BuildingDeck& deck);
	void loadCharacterHand(CharacterHand& hand);

private:

};


