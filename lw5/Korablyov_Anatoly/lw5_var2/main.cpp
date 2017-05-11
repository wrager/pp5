#include <iostream>
#include <vector>
#include "SortBatcher.h"

int main()
{
	std::vector<unsigned> number = { };
	
	std::cout << "{ ";
	for (auto it : number)
	{
		std::cout << it << " ";
	}
	std::cout << "}" << std::endl;

	CSortBatcher sortBatch;
	std::vector<unsigned> res = sortBatch.sortBatcher(number);

	std::cout << "{ ";
	for (auto it : res)
	{
		std::cout << it << " ";
	}
	std::cout << "}" << std::endl;
}