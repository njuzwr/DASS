#pragma once
#include <array>
#include <iostream>
#define MAXSIZE 100

namespace my
{
	template <typename T>
	class DoubleStack
	{
	public:
		struct LStack
		{
			int theSize = 0;
			void push(T & object)
			{
				if (this->theSize + RStack::theSize < MAXSIZE)
				{
					data[theSize] = object;
					++theSize;
				}
				else std::cerr << "Array is full!" << std::endl;
			}
			T top() const { return data[theSize]; }
			void pop()
			{
				if (theSize == 0)
					std::cerr << "LStack is empty" << std::endl;
				else
					--theSize;
			}
			bool empty() const { return (theSize == 0); }
		};
		struct RStack
		{
			int theSize = 0;
			void push(T & object)
			{
				if (this->theSize + LStack::theSize < MAXSIZE)
				{
					data[MAXSIZE - 1 - theSize] = object;
					++theSize;
				}
				else std::cerr << "Array is full!" << std::endl;
			}
			T top() const { return data[MAXSIZE - 1 - theSize]; }
			void pop()
			{
				if (theSize == 0)
					std::cerr << "RStack is empty" << std::endl;
				else
					--theSize;
			}
			bool empty() const { return (theSize == 0); }
		};

	private:
		std::array<T, MAXSIZE> data;

	};
}