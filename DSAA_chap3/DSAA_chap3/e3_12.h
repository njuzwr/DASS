#pragma once
#include  <iostream>

namespace ans
{
	template <typename Object>
	struct Node
	{
		Object data;
		Node *next;
		Node (const Object &d = Object(), Node *n = nullptr) : data(d), next(n) { }
	};
	template <typename Object>
	class singleList
	{
	public:
		singleList() { init(); }
		~singleList() { eraseList(head); }
		singleList(const singleList & rhs)
		{
			eraseList(head);
			init();
			*this = rhs;
		}
		bool add(Object x)
		{
			if (contains(x))
				return false;
			else
			{
				Node<Object> *ptr = head->next;	// 用于循环计数
				Node<Object> *trailer = head;	// 用于记录位置
				while (ptr && ptr->data < x)	// 先找到插入节点的位置，再插入数据
				{
					trailer = ptr;
					ptr = ptr->next;
				}
				trailer->next = new Node<Object>(x);
				trailer->next->next = ptr;
				++theSize;
			}
			return true;
		}
		bool sorted_add(Object x)	// my code
		{
			if (contains(x))
				return false;
			else
			{
				Node<Object> *ptr = new Node<Object>(x);
				Node<Object> *curr_ptr = head->next;
				while (curr_ptr != nullptr)
				{
					if (curr_ptr->data <= x && curr_ptr->next->data >= x)
					{
						ptr->next = curr_ptr->next;
						curr_ptr->next = ptr;
						++theSize;
					}
					if (curr_ptr->next == nullptr)
					{
						ptr->next = nullptr;
						curr_ptr->next = ptr;
						++theSize;
					}
					curr_ptr = curr_ptr->next;
				}
				return true;
			}
		}
		bool remove(Object x)
		{
			if (!contains(x))
				return false;
			else
			{
				Node<Object> *ptr = head->next;
				Node<Object> *trailer;
				while (ptr->data != x)
				{
					trailer = ptr;
					ptr = ptr->next;
				}
				trailer->next = ptr->next;
				delete ptr;
				--theSize;
			}
			return true;
		}
		int size() { return theSize; }
		void print()
		{
			Node<Object> *ptr = head->next;
			while(ptr != nullptr)
			{
				std::cout << ptr->data << " ";
				ptr = ptr->next;
			}
			std::cout << std::endl;
		}
		bool contains(const Object & x)
		{
			Node<Object> *ptr = head->next;
			while(ptr!=nullptr && ptr->data <= x)
			{
				if (x == ptr->data)
					return true;
				else
					ptr = ptr->next;
			}
			return false;
		}
		void init()
		{
			theSize = 0;
			head = new Node<Object>;
			head->next = nullptr;
		}
		void eraseList(Node<Object> *h)
		{
			Node<Object> *ptr = h;
			Node<Object> *nextPtr;
			while(ptr != nullptr)
			{
				nextPtr = ptr->next;
				delete ptr;
				ptr = nextPtr;
			}
		}
		private:
			Node<Object> *head;
			int theSize;
	};
}