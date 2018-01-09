#pragma once

#include <deque>

#include "Deck.h"

using namespace std;

template<typename T>
class Hand : public Deck<T> {

public:

	const typename deque<T>::iterator handBegin() const { return stack.begin(); }
	const typename deque<T>::iterator handEnd() const { return stack.end(); }
	const int handAmount() const { return static_cast<int>(stack.size()); }

	typename deque<T>::iterator handBegin() { return stack.begin(); }
	typename deque<T>::iterator handEnd() { return stack.end(); }
	int handAmount() { return static_cast<int>(stack.size()); }

	T handPull(typename deque<T>::iterator obj)
	{
		T ret = move(*obj);
		stack.erase(obj);
		return ret;
	}

private:

};
