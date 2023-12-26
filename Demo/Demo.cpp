#include <iostream>
#include "../LinkedListSmartPtr/List.h"

int main() 
{
	List<int> list{ 1,2,34,6,7,8 };
	std::cout << list;
	return 0;
}