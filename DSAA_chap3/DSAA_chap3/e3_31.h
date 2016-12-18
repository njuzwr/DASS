#pragma once
#include <forward_list>

namespace my
{
	template <typename T>
	class MyDeque
	{
	public:
		void push(const T & obj) { data.insert_after(iter, obj); }
		T top() { return data.front(); }
		void pop() { data.erase_after(iter); }
	private:
		std::forward_list<T> data;
		auto iter = data.before_begin();
	};
}
namespace ans
{
	template <typename T>
	struct Node
	{
		Node() { next = nullptr; }
		Node(T obj) : data(obj) {}
		Node(T obj, Node *ptr) : data(obj), next(ptr) {}
		T data;
		Node *next;
	};
	template <typename T>
	class Stack
	{
	public:
		Stack() { head = nullptr; }
		~Stack() { while (head) pop(); }
		void push(T obj)
		{
			Node<T> *ptr = new Node<T>(obj, head);
			head = ptr;
		}
		T top() { return (head->data); }
		void pop()
		{
			Node<T> *ptr = head->next;
			delete head;
			head = ptr;
		}
	private:
		Node<T> *head;
	};

	template <typename T>
	class Queue
	{
	public:
		Queue() { front = nullptr; rear = nullptr; }
		~Queue() { while (front) deque(); }
		void enque(T obj)
		{
			Node<T> *ptr = new Node<T>(obj, nullptr);
			if (rear)	// 这个判断语句非常好，解决了入空队列和非空队列的情况
				rear = rear->next = ptr;	// rear->next并没有赋值nullptr，而是自身
			else  // first node inserted
				front = rear = ptr;
		}
		T deque()
		{
			T temp = front->data;
			Node<T> *ptr = front;
			if (front->next == nullptr) // only one node
				front = rear = nullptr;
			else
				front = front->next;
			delete ptr;
			return tmp;
		}
	private:
		Node<T> *front;
		Node<T> *rear;

	};
}