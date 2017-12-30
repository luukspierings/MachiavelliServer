#include "stdafx.h"
#include "RandomGenerator.h"

int RandomGenerator::generate(int min, int max)
{
	// generates nummer between min and max, includes min and max.
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}
