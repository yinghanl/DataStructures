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
	while (mSize != 0)
	{
		pop_back();
	}
}

template<typename T>
int LinkedList<T>::size()
{
	return mSize;
}

template<typename T>
void LinkedList<T>::push_back(T val)
{
	ListItem* toInsert = new ListItem(val);
	toInsert->next = nullptr;
	if (mTail == nullptr)
	{
		toInsert->prev = nullptr;
		mHead = toInsert;
		mTail = mHead;
	}
	else
	{
		mTail->next = toInsert;
		toInsert->prev = mTail;
		mTail = toInsert;
	}
	mSize++;
}

template<typename T>
void LinkedList<T>::push_front(T val)
{
	ListItem* toinsert = new ListItem(val);
	toInsert->prev = nullptr;
	if (mHead == nullptr)
	{
		toInsert->next = nullptr;
		mHead = toInsert;
		mTail = mHead;
	}
	else
	{
		mHead->prev = toInsert;
		toInsert->next = mHead;
		mHead = toInsert;
	}
	mSize++;
}

template<typename T>
void LinkedList<T>::pop_back()
{
	if (mTail == nullptr)
	{
		return;
	}
	else if (mHead == mTail)
	{
		delete mTail;
		mHead = nullptr;
		mTail = nullptr;
		mSize--;
	}
	else
	{
		ListItem* previous = mTail->prev;
		previous->next = nullptr;
		delete mTail;
		mTail = previous;
		mSize--;
	}
}

template<typename T>
void LinkedList<T>::pop_front()
{
	if (mHead == nullptr)
	{
		return;
	}
	else if (mHead == mTail)
	{
		delete mHead;
		mHead = nullptr;
		mTail = nullptr;
		mSize--;
	}
	else
	{
		ListItem* next = mHead->next;
		next->prev = nullptr;
		delete mHead;
		mHead = next;
		mSize--;
	}
}

template<typename T>
auto LinkedList<T>::begin()
{
	return LinkedListIterator(mHead);
}

template<typename T>
auto LinkedList<T>::end()
{
	return LinkedListIterator(nullptr);
}

#endif