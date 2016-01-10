#include "Vector.h"
#ifndef _VECTOR_CPP_
#define _VECTOR_CPP_

template <typename T>
Vector<T>::Vector()
{
	mStorage = new T[2];
	mCapacity = 2;
	mSize = 0;
}

template <typename T>
Vector<T>::~Vector()
{
	delete mStorage;
}

template<typename T>
int Vector<T>::size()
{
	return mSize;
}

template<typename T>
void Vector<T>::push_back(T val)
{
	if (mSize == mCapacity)
	{
		T* newStorage = new T[mCapacity * 2];
		for (int i = 0; i < mSize; i++)
		{
			newStorage[i] = mStorage[i];
		}
		delete mStorage;
		mStorage = newStorage;
		mCapacity *= 2;

		mStorage[mSize] = val;
		mSize++;
	}
	else
	{
		mStorage[mSize] = val;
		mSize++;
	}
}

template<typename T>
void Vector<T>::pop_back(T val)
{
	mSize--;
}

template<typename T>
T Vector<T>::operator[](int index)
{
	return mStorage[index];
}

#endif