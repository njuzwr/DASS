#pragma once
#include <utility>
template <typename Object>
class List
{
private:
	struct Node;
public:
	class const_iterator
	{
	public:
		const_iterator() : current{ nullptr } {}
		const Object & operator* () const { return retrieve(); }
		const_iterator & operator++ ()
		{
			current = current->next;
			return *this;
		}
		const_iterator operator++(int)
		{
			const_iterator old = *this;
			++(*this);
			return old;
		}
		bool operator== (const const_iterator & rhs) const
		{
			return current == rhs.current;
		}
		bool operator!= (const const_iterator & rhs) const
		{
			return !(*this == rhs);
		}

		// exercise 3.14
		//const_iterator operator+(int k) const
		//{
		//	for (auto i = 0; i < k; ++i)
		//		++*this;
		//	return *this;
		//}
		// answer:
		const_iterator & operator+ (int k)
		{
			const_iterator advanced = *this;
			for (int i = 0; i < k; ++i)
				advanced.current = advanced.current->next;
			return advanced;
		}
	protected:
		Node *current;
		Object & retrieve() const { return current->data; }
		const_iterator(Node *p) : current{ p } {}
		friend class List<Object>;
	};
	class iterator : public const_iterator
	{
	public:
		iterator() {}	// 为什么这里用default constructor?
		Object & operator* ()
		{
			return const_iterator::retrieve();
		}
		const Object & operator* ()const
		{
			return const_iterator::operator* ();
		}
		iterator & operator++ ()
		{
			this->current = this->current->next;
			return *this;
		}
		iterator operator++ (int)
		{
			iterator old = *this;
			++(*this);
			return old;
		}
		/*
		// exercise 3.13
		// add support for operator -
		// Errata: operator-- not operator-

		int & operator- (iterator & rhs)
		{
			iterator iter = rhs;
			int diff = 0;
			while (iter->current != this->current)
			{
				++diff;
				++iter;
			}
			return diff;
		}
		*/
	protected:
		iterator(Node *p) : const_iterator{p} {}
		friend class List<Object>;
	};

	// exercise 3.16
	class const_reverse_iterator
	{
	public:
		const_reverse_iterator() : current{nullptr} {}
		const Object & operator* () const { return retrieve(); }
		const_reverse_iterator & operator++ ()
		{
			current = current->prev;
			return *this;
		}
		const_reverse_iterator operator++(int)
		{
			const_reverse_iterator old = *this;
			++(*this);
			return old;
		}
		const_reverse_iterator & operator-- ()
		{
			current = current->next;
			return *this;
		}
		const_reverse_iterator operator--(int)
		{
			const_reverse_iterator old = *this;
			--(*this);
			return old;
		}
		bool operator== (const const_reverse_iterator & rhs) const
		{
			return current == rhs.current;
		}
		bool operator!= (const const_reverse_iterator & rhs) const
		{
			return !(*this == rhs);
		}
		const_reverse_iterator rbegin()
		{
			Node *p = this->current;
			while (p->next != nullptr)
				p = p->next;
			return const_reverse_iterator{ p };
		}
		const_reverse_iterator rend()
		{
			Node *p = this->current;
			while (p->prev != nullptr)
				p = p->prev;
			return const_reverse_iterator{ p };
		}
	protected:
		Node *current;
		Object & retrieve() const { return current->data; }
		const_reverse_iterator(Node *p) : current{ p } {}
		friend class List<Object>;
	};
	class reverse_iterator : public const_reverse_iterator
	{
	public:
		reverse_iterator() { }
		reverse_iterator & operator++ ()
		{
			this->current = this->current->prev;
			return *this;
		}
		reverse_iterator operator++(int)
		{
			reverse_iterator old = *this;
			++(*this);
			return old;
		}
		reverse_iterator & operator-- ()
		{
			this->current = this->current->next;
			return *this;
		}
		reverse_iterator operator--(int)
		{
			reverse_iterator old = *this;
			--(*this);
			return old;
		}
		reverse_iterator rbegin()
		{
			Node *p = this->current;
			while (p->next != nullptr)
				p = p->next;
			return reverse_iterator{ p };
		}
		reverse_iterator rend()
		{
			Node *p = this->current;
			while (p->prev != nullptr)
				p = p->prev;
			return reverse_iterator{ p };
		}
	protected:
		reverse_iterator(Node *p) : const_reverse_iterator{p} {}
		friend class List<Object>;
	};
	// contents above is exercise 3.16, writen by myself
public:
	List();
	List(const List &rhs);
	~List();
	List & operator= (const List & rhs);
	List & operator= (List && rhs);

	iterator begin() { return{ head->next }; }
	const_iterator begin() const { return{ head->next }; }
	iterator end() { return{ tail }; }
	const_iterator end() const { return{ tail }; }

	int size() const { return theSize; }
	bool empty() const { return size() == 0; }
	void clear()
	{
		while (!empty())
			pop_front();
	}

	Object & front() { return *begin(); }
	const Object & front() const { return *begin(); }
	Object & back() { return *--end(); }
	const Object & back() const { return *--end(); }
	void push_front(const Object & x) { insert(begin(), x); }
	void push_front(Object && x) { insert(begin(), std::move(x)); }
	void push_back(const Object & x) { insert(end(), x); }
	void push_back(Object && x) { insert(end(), std::move(x)); }
	void pop_front() { erase(begin()); }
	void pop_back() { erase(--end()); }

	iterator insert(iterator itr, const Object & x);
	iterator insert(iterator itr, Object && x);
	iterator erase(iterator itr);
	iterator erase(iterator from, iterator to);

	// exercise3.15
	//void splice(iterator position, List<Object> & lst)
	//{
	//	lst.tail->next = *position;
	//	*position->prev = lst.tail;
	//	*--position->next = lst.head;
	//	delete lst.head;
	//	delete lst.tail;
	//}
	// answer:
	// head和tail节点没有数据
	// 双向链表的插入操作
	void splice(iterator itr, List<Object> & lst)
	{
		itr.assertIsValid();
		if (itr.theList != this)
			throw IteratorMisMatchException();
		Node *p = itr.current;
		theSize += lst.size();
		p->prev->next = lst.head->next;
		lst.head->next->prev = p->prev;
		lst.tail->prev->next = p;
		p->prev = lst->tail->prev;
		lst.init();
	}
private:
	int theSize;
	Node *head;
	Node *tail;
	void init();
};

template <typename Object>
struct List<Object>::Node
{
	Object data;
	Node *prev;
	Node *next;

	Node(const Object & d = Object(), Node *p = nullptr, Node *n = nullptr)
		: data(d), prev{p}, next{n} {}
	Node(Object && d, Node *p = nullptr, Node *n = nullptr)
		: data(std::move(d)), prev{p}, next{n} {}
};