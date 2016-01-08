#ifndef _LINKEDLIST_CPP_
#define _LINKEDLIST_CPP_

#include "LinkedList.h"

template <typename T>
LinkedList<T>::LinkedList()
{
	mHead = nullptr;
	mTail = nullptr;
	mSize = 0;
}

template<typename T>
LinkedList<T>::~LinkedList()
{
}

template<typename T>
void LinkedList<T>::push_back(T val)
{
	ListItem* toInsert = new ListItem(val);
	if (mHead == nullptr)
	{
		mHead = toInsert;
		mTail = mHead;
	}
	else
	{
		mTail->next = toInsert;
		mTail = toInsert;
	}
}

#endif