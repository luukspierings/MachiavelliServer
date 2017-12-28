#include "stdafx.h"
#include "CharacterFactory.h"

vector<unique_ptr<Character>> CharacterFactory::getCharacters()
{

	vector<unique_ptr<Character>> characters {};

	vector<vector<string>> data = fileHandler.getValues();

	// TODO: change order of characters by first value.
	for (auto row : data) {
		if (row[1] == "Moordenaar") characters.push_back(make_unique<Assassin>());
		if (row[1] == "Dief") characters.push_back(make_unique<Robber>());
		if (row[1] == "Magiër") characters.push_back(make_unique<Mage>());
		if (row[1] == "Koning") characters.push_back(make_unique<King>());
		if (row[1] == "Prediker") characters.push_back(make_unique<Preacher>());
		if (row[1] == "Koopman") characters.push_back(make_unique<Merchant>());
		if (row[1] == "Bouwmeester") characters.push_back(make_unique<Builder>());
		if (row[1] == "Condottiere") characters.push_back(make_unique<Condottiere>());
	}

	return characters;
}
