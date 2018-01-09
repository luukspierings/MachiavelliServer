#pragma once

#include "Deck.h";

template<typename T>
class Hand : public Deck<T> {

public:

	T::Iterator begin() const { return stack.begin(); }
	T::Iterator end() const { return stack.end(); }
	T::Iterator amount() const { return stack.amount(); }

	T pull(T::Iterator obj)
	{
		T ret = move(obj);
		stack.erase(obj);
		return ret;
	}


};