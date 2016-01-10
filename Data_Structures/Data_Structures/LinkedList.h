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
class LinkedListIterator
{
public:
	LinkedListIterator(ListItem* item)
	{
		current = item;
	}
	void operator++()
	{
		current = current->next;
	}
	T operator*()
	{
		return current->val;
	}
	bool operator==(LinkedListIterator target)
	{
		return (current == target.current);
	}

	bool operator!=(LinkedListIterator target)
	{
		return (current != target.current);
	}
private:
	ListItem* current;
};

public:
	LinkedList();
	~LinkedList();
	int size();
	void push_back(T val);
	void push_front(T val);
	void pop_back();
	void pop_front();
	auto begin();
	auto end();

private:
	ListItem* mHead;
	ListItem* mTail;
	int mSize;
};

#include "LinkedList.cpp"
