#include "stdafx.h"
#include "BuildingDeck.h"

std::ifstream & operator>>(std::ifstream & ifstream, BuildingDeck & characterDeck)
{
	std::cout << "Hallo" << std::endl;

	return ifstream;
}
