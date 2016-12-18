#pragma once
#include <iostream>
namespace my
{
	struct Node
	{
		int data;
		Node * next;
		Node(const int &d = int(), Node *p = nullptr) : data(d), next(p) { }
	};
	class Singly_linked_list
	{
	public:
		Singly_linked_list() { header = nullptr; }
		size_t size(Node * hdp)
		{
			size_t s = 0;
			for (Node *p = hdp; p->next != nullptr; ++s, p = p->next);
			return s;
		}
		void print(Node *hdp)
		{
			for (Node *p = hdp; p->next != nullptr; p = p->next)
				std::cout << p->data << std::endl;
		}
		bool exist(int x, Node * hdp)
		{
			for (Node *p = hdp; p->next != nullptr; p = p->next)
			{
				if (p->data == x)
					return true;
			}
			return false;
		}
		void insert(int x, Node *hdp, Node * pos)
		{
			if (!exist(x, hdp))
			{
				Node * temp = new Node(x);
				temp->next = pos->next;
				pos->next = temp;
			}
		}
		void remove(int x, Node *hdp, Node *pos)
		{
			if (exist(x, hdp))
			{
				Node *tmp = pos->next;
				pos->next = pos->next->next;
				delete(tmp);
			}
		}
	private:
		Node * header;
	};
}

namespace ans
{
	template <typename Object>
	struct Node
	{
		Object data;
		Node * next;
		Node (const Object & d = Object(), Node *n = nullptr)
			: data(d), next(n) {}
	};

	template <typename Object>
	class SingleList
	{
	public:
		SingleList() { init(); }
		~SingleList() { eraseList(head); }
		SingleList(const SingleList & rhs)
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
				Node<Object> * ptr = new Node<Object>(x);
				ptr->next = head->next;
				head->next = ptr;
				++theSize;
			}
			return true;
		}
	
		bool remove(Object x)
		{
			if (!contains(x))
				return false;
			else
			{
				Node<Object> *ptr = head->next;
				Node<Object> *trailer = nullptr;
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
		int size() const{ return theSize; }
		void print() const
		{
			Node<Object> *ptr = head->next;
			while(ptr != nullptr)
			{
				std::cout << ptr->data << " ";
				ptr = ptr->next;
			}
			std::cout << std::endl;
		}
		bool contains(const Object &x)
		{
			Node<Object> *ptr = nullptr;
			while ( ptr!= nullptr)
			{
				if (x == ptr->data)
					return true;
				else
					ptr = ptr->next;
				return false;
			}
		}
		void init()	// call init() in default constructor and copy constructor
		{
			theSize = 0;
			head = new Node<Object>;
			head->next = nullptr;
		}
		void eraseList(Node<Object> *h)
		{
			Node<Object> *ptr = h;
			Node<Object> *nextptr = nullptr;
			while (ptr != nullptr)
			{
				nextptr = ptr->next;
				delete ptr;
				ptr = nextptr;
			}
		}
	private:
		Node<Object> *head;
		int theSize;
	};
}
