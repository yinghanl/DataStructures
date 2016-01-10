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

	system("PAUSE");
	return 0;

}