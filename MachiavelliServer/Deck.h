#pragma once

#include <algorithm>
#include <deque>

#include "RandomGenerator.h"

using namespace std;

template<typename T>
class Deck {
public:

	void shuffle_stack() {
		shuffle(stack.begin(), stack.end(), RandomGenerator::getInstance().getGenerator());
	}

	bool stack_empty() const { return stack.empty(); }
	bool discard_pile_empty() const { return discard_pile.empty(); }

	T draw() {
		if (stack_empty()) merge_stacks();
		T buffer = move(stack.front());
		stack.pop_front();
		return buffer;
	}

	T top() {
		return stack.front();
	}

	//void discard(const T& card) {
	//	discard_pile.push_front(move(card));
	//}
	void discard(T&& card) {
		discard_pile.push_front(move(card));
	}

	//void push_bottom_stack(const T& card) {
	//	stack.push_back(move(card));
	//}
	void push_bottom_stack(T&& card) {
		stack.push_back(move(card));
	}

	void push_top_stack(const T& card) {
		stack.push_front(move(card));
	}
	void push_top_stack(T&& card) {
		stack.push_front(move(card));
	}

	void merge_stacks(bool shuffle_afterwards = true) {

		for (auto it = stack.begin(); it != stack.end();) {
			discard_pile.push_front(move(*it));
			it = stack.erase(it);
		}
		swap(stack, discard_pile);

		if (shuffle_afterwards) shuffle_stack();

	}

	void clearAll() {
		stack.clear();
		discard_pile.clear();
	}

protected:
	deque<T> stack;
	deque<T> discard_pile;

};
