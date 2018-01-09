#include "stdafx.h"
#include "CharacterHand.h"

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
		
		characterHand.addCharacter(tokens[1], stoi(tokens[1])); // could throw exception
	}
	return ifstream;
}

void CharacterHand::addCharacter(string name, int order) {
	if (name == "Moordenaar") push_top_stack(Assassin(order));
	/*if (name == "Dief") push_top_stack(Robber{ order });
	if (name == "Magiër") push_top_stack(Mage{ order });
	if (name == "Koning") push_top_stack(King{ order });
	if (name == "Prediker") push_top_stack(Preacher{ order });
	if (name == "Koopman") push_top_stack(Merchant{ order });
	if (name == "Bouwmeester") push_top_stack(Builder{ order });
	if (name == "Condottiere") push_top_stack(Condottiere{ order });*/
}

void CharacterHand::sortCharacters()
{
	//sort(stack.begin(), stack.end(), ordersort);
}

