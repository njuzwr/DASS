#pragma once
#include <vector>
namespace my
{
	
}
namespace ans
{
	template <typename T>
	class Queue
	{
	public:
		Queue(int s) : maxSize(s), front(0), rear(0) { elements.resize(maxSize); }
		Queue() { maxSize = 100; front = 0; rear = 0; elements.resize(maxSize); }
		~Queue() { while (front != rear) deque(); }
		void enque(T obj)
		{
			if (!full())
			{
				elements[rear] = obj;
				rear = (rear + 1) % maxSize;
			}
		}
		T deque()
		{
			T temp;
			if (!empty())
			{
				temp = elements[front];
				front = (front + 1) % maxSize;
				return temp;
			}
		}
		bool empty() const { return front == rear; }
		bool full() const { return (rear + 1) % maxSize == front; }
	private:
		int front, rear;
		int maxSize;
		std::vector<T> elements;
	};
}