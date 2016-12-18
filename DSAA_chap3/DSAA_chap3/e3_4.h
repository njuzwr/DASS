#pragma once
#include <list>
#include <iostream>

namespace my
{
	// 使用const reference 更佳
	template <typename Object>
	void intersection(std::list<Object> L1, std::list<Object> L2)
	{
		auto iter1 = L1.begin();
		for (auto iter2 = L2.begin(); iter2 != L2.end() && iter1 != L1.end();)
		{
			if (*iter1 == *iter2)
			{
				std::cout << *iter1 << std::endl;
				++iter1;
				++iter2;
			}
			else if (*iter1 < *iter2)
				++iter1;
			else
				++iter2;
		}
	}

	template <typename Object>
	void compute_union(std::list<Object> L1, std::list<Object> L2)
	{
		auto iter1 = L1.begin();
		for (auto iter2 = L2.begin(); iter2 != L2.end();)
		{
			if (iter1 != L1.end())
			{
				if (*iter1 < *iter2)
				{
					std::cout << *iter1 << std::endl;
					++iter1;
				}
				else if (*iter1 == *iter2)
				{
					std::cout << *iter1 << std::endl;
					++iter1;
					++iter2;
				}
				else
				{
					std::cout << *iter2 << std::endl;
					++iter2;
				}
			}
			else
			{
				std::cout << *iter2 << std::endl;
				++iter2;
			}

		}
		while (iter1 != L1.end())
		{
			std::cout << *iter1 << std::endl;
			++iter1;
		}
	}
}

namespace ans
{
	// Assumes both input lists are sorted
	template <typename Object>
	std::list<Object> intersection(const std::list<Object> & L1,
								   const std::list<Object> & L2)
	{
		std::list<Object> intersect;
		typename std::list<Object>::const_iterator iterL1 = L1.begin();
		// auto iterL1 = L1.cbegin();
		typename std::list<Object>::const_iterator iterL2 = L2.begin();
		while (iterL1 != L1.end() && iterL2 != L2.end())
		{
			if (*iterL1 == *iterL2)
			{
				intersect.push_back(*iterL1);
				++iterL1;
				++iterL2;
			}
			else if (*iterL1 < *iterL2)
				++iterL1;
			else
				++iterL2;
		}
		return intersect;
	}

	// Assumes both input lists are sorted
	// 没有考虑while循环不能满足的情况，也即提前到达一个list的end
	template <typename Object>
	std::list<Object> listUnion (const std::list<Object> & L1, const std::list<Object> & L2)
	{
		std::list<Object> result;
		typename std::list<Object>::const_iterator iterL1 = L1.begin();
		typename std::list<Object>::const_iterator iterL2 = L2.begin();
		while(iterL1 != L1.end() && iterL2 != L2.end())
		{
			if (*iterL1 == *iterL2)
			{
				result.push_back(*iterL1);
				std::cout << *iterL1 << std::endl;
				++iterL1;
				++iterL2;
			}
			else if (*iterL1 < *iterL2)
			{
				result.push_back(*iterL1);
				std::cout << *iterL1 << std::endl;
				++iterL1;
			}
			else
			{
				result.push_back(*iterL2);
				std::cout << *iterL2 << std::endl;
				++iterL2;
			}
			
		}
		return result;
	}
}