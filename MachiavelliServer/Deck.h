#pragma once

#include <algorithm>
#include <deque>

#include "RandomGenerator.h"

using namespace std;

template<typename T>
class Deck {
public:
	Deck() {
	}

	Deck(std::initializer_list<T> cards) {
	}

	template<typename Iter>
	Deck(Iter b, Iter e) {

	};

	void shuffle_stack() {
		shuffle(stack.begin(), stack.end(), RandomGenerator::getInstance().generator());
	}

	bool stack_empty() const { return stack.empty(); }
	bool discard_pile_empty() const { return discard_pile.empty(); }

	T draw() {
		if (stack_empty()) merge_stacks();
		T buffer = move(stack.front());
		stack.pop_front();
		return buffer;
	}

	void discard(const T& card) {
		discard_pile.push_front(move(card));
	}
	void discard(T&& card) {
		discard_pile.push_front(move(card));
	}

	void push_bottom_stack(const T& card) {
		stack.push_back(move(card));
	}
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



		if (shuffle_afterwards) shuffle_stack();
	}


private:
	deque<T> stack;
	deque<T> discard_pile;

};