#include "stdafx.h"
#include "RandomGenerator.h"

int RandomGenerator::generate(int min, int max)
{
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}
