#pragma once
#include <iostream>
#include <list>

void printLots(const std::list<int> & L, const std::list<int> & P)
{
	
	for (auto loc : P)
	{
		auto b = L.cbegin();
		for (int i = 0; i < loc; ++b, ++i);
		std::cout << *b << std::endl;
	}
}

template <typename Object>
void printLots2(std::list<Object> L, std::list<int> P)
{
	std::list<int>::const_iterator pIter;
	typename std::list<Object>::const_iterator lIter;
	int start = 0;
	lIter = L.begin();
	for (pIter = P.begin(); pIter != P.end() && lIter != L.end(); ++pIter)
	{
		while (start < *pIter && lIter != L.end())
		{
			++start;
			++lIter;
		}
		if (lIter != L.end())
			std::cout << *lIter << std::endl;
	}

}