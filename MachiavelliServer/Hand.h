#pragma once


#include <deque>

#include "Deck.h";

using namespace std;


template<typename T>
class Hand : public Deck<T> {

public:

	typename deque<T>::iterator HandBegin() const { return stack.begin(); }
	typename deque<T>::iterator HandEnd() const { return stack.end(); }
	typename deque<T>::iterator HandAmount() const { return stack.amount(); }

	T HandPull(typename deque<T>::iterator obj)
	{
		T ret = move(obj);
		stack.erase(obj);
		return ret;
	}


};