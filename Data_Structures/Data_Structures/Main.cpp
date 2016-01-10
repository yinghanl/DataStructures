#include <iostream>
#include "LinkedList.h"
#include "Vector.h"

int main()
{

	LinkedList<int> list;
	list.push_back(1);
	list.push_back(2);

	for (auto i = list.begin(); i != list.end(); ++i)
	{
		std::cout << (*i) << std::endl;

	}

	Vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	for (int i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i] << std::endl;
	}

	system("PAUSE");
	return 0;

}