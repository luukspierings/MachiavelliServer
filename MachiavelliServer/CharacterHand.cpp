#include "stdafx.h"
#include "CharacterHand.h"

<<<<<<< HEAD
std::ifstream & operator>>(std::ifstream & ifstream, CharacterHand & characterHand)
{
=======
#include "Assassin.h"
#include "Builder.h"
#include "Condottiere.h"
#include "King.h"
#include "Mage.h"
#include "Merchant.h"
#include "Preacher.h"
#include "Robber.h"

bool ordersort(const Character& a, const Character& b) {
	return (a.getOrder() < b.getOrder());
}

std::ifstream & operator>>(std::ifstream & ifstream, CharacterHand & characterHand)
{	
	char split_char = ';';
	for (string row_line; getline(ifstream, row_line);)
	{
		istringstream split(row_line);
		vector<string> tokens;
		for (string each; getline(split, each, split_char);) tokens.push_back(each);
		
		characterHand.push_top_stack(characterHand.makeCharacter(tokens[1], stoi(tokens[1]))); // could throw exception
	}
>>>>>>> c4f65641775641dfbb3cef7f772c040b282f1778
	return ifstream;
}

Character CharacterHand::makeCharacter(string name, int order) {
	if (name == "Moordenaar") return Assassin{order};
	if (name == "Dief") return Robber{ order };
	if (name == "Magiër") return Mage{ order };
	if (name == "Koning") return King{ order };
	if (name == "Prediker") return Preacher{ order };
	if (name == "Koopman") return Merchant{ order };
	if (name == "Bouwmeester") return Builder{ order };
	if (name == "Condottiere") return Condottiere{ order };
		
	throw std::invalid_argument("received name of unknown character");
}

void CharacterHand::sortCharacters()
{
	sort(stack.begin(), stack.end(), ordersort);
}

