#pragma once
#include <utility>
namespace my
{
	template <typename T>
	class MyList
	{
		struct Node
		{
			T data;
			Node *next;
			Node(const T &d = T(), Node *n = nullptr)
				: data(d), next(n) {}
			Node(T &&d, Node *n = nullptr)
				: data(std::move(d), next(n)) {}
		};

	private:
		int theSize;
		void init();

	};
	
}
