#pragma once
template <typename T>
class Vector
{
public:
	Vector();
	~Vector();
	int size();
	void push_back(T val);
	void pop_back(T val);

private:
	T *mStorage;
	int mSize;
	int mCapacity;
};

#include "Vector.cpp"