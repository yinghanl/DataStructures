#pragma once

template <typename T>
class LinkedList
{
public:

struct ListItem
{
	ListItem* next;
	ListItem* prev;
	T val;
	ListItem(T val)
	{
		this->val = val;
	}
};

public:
	LinkedList();
	~LinkedList();
	void push_back(T val);
	void push_front(T val);
	void pop_back();
	void pop_front();

private:
	ListItem* mHead;
	ListItem* mTail;
	int mSize;
};

#include "LinkedList.cpp"
