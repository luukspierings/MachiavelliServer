#pragma once

#include <memory>

class BuildingDeck;
class CharacterHand;

using namespace std;

class DeckFactory {

public:
	void loadBuildingDeck(BuildingDeck& deck);
	void loadCharacterHand(CharacterHand& hand);

private:

};


