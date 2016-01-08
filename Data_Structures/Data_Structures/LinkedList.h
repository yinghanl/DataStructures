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

private:
	ListItem* mHead;
	ListItem* mTail;
	int mSize;
};

#include "LinkedList.cpp"
