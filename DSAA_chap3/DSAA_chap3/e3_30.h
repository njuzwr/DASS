#pragma once
#include <array>
#define MAXSIZE 100

template <typename T>
class SelfAdjustingList
{
public:
	void insert(const T & obj)
	{
		data.push(obj);
		++theSize;
	}
	bool find(const T & obj)
	{
		for (int i = 0; i < theSize; ++i)
		{
			if(data.at(i) == obj)
			{
				for(int j = i; j < theSize; ++j)
					data.at(j) = data.at(j + 1);
				data.at(theSize) = obj;
				return true;
			}
		}
		return false;
	}
private:
	std::array<T, MAXSIZE> data;
	int theSize;
};