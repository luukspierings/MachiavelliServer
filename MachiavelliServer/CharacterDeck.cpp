#include "stdafx.h"
#include "CharacterDeck.h"

std::ifstream & operator>>(std::ifstream & ifstream, CharacterDeck & characterDeck)
{
	std::string test;

	ifstream >> test;
	std::cout << test << std::endl;

	return ifstream;
}
