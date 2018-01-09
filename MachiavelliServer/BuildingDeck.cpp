#include "stdafx.h"
#include "BuildingDeck.h"

std::ifstream & operator>>(std::ifstream & ifstream, BuildingDeck & characterDeck)
{
	char split_char = ';';

	for (string row_line; getline(ifstream, row_line);)
	{
		std::istringstream split(row_line);
		std::vector<std::string> tokens;
		for (std::string each; std::getline(split, each, split_char); tokens.push_back(each));
		
		CardColor color = CardColor::NONE;
		if (tokens[2] == "geel") color = CardColor::YELLOW;
		if (tokens[2] == "groen") color = CardColor::GREEN;
		if (tokens[2] == "blauw") color = CardColor::BLUE;
		if (tokens[2] == "rood") color = CardColor::RED;
		if (tokens[2] == "lila") color = CardColor::LILAC;

		if (color != CardColor::NONE) 
		{
			characterDeck.push_top_stack(Building(tokens[0], stoi(tokens[1]), color));
		};
	}

	return ifstream;
}
