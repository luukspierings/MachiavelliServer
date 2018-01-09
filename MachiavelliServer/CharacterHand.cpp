#include "stdafx.h"
#include "CharacterHand.h"

std::ifstream & operator>>(std::ifstream & ifstream, CharacterHand & characterHand)
{
	std::string test;

	ifstream >> test;
	std::cout << test << std::endl;

	return ifstream;
}
