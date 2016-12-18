#pragma once
#include <algorithm>

template <typename Object>
class Vector
{
public:
	explicit Vector(int initSize=0) : theSize{initSize}, theCapacity{initSize + SPARE_CAPACITY}
	{
		objects = new Object[theCapacity];
	}

	Vector(const Vector & rhs) : theSize{rhs.theSize}, theCapacity{rhs.theCapacity},
		objects{nullptr}
	{
		objects = new Object[theCapacity];
		for (int k = 0; k < theSize; ++k)
			objects[k] = rhs.objects[k];
	}

	Vector & operator= (const Vector & rhs)
	{
		Vector copy = rhs;
		std::swap(*this, copy);
		return *this;
	}

	~Vector()
	{
		delete[] objects;
	}

	Vector(Vector && rhs) :theSize{ rhs.theSize }, theCapacity{rhs.theCapacity}, objects{rhs.objects}
	{
		rhs.objects = nullptr;
		rhs.theSize = 0;
		rhs.theCapacity = 0;
	}

	Vector & operator= (Vector &&rhs)
	{
		std::swap(theSize, rhs.theSize);
		std::swap(theCapacity, rhs.theCapacity);
		std::swap(objects, rhs.objects);

		return *this;
	}

	void resize(int newSize)
	{
		if (newSize > theCapacity)
			reserve(newSize * 2);
		theSize = newSize;
	}

	void reserve(int newCapacity)
	{
		if (newCapacity < theSize)
			return;
		Object * newArray = new Object[newCapacity];
		for (int k = 0; k < theSize; ++k)
			newArray[k] = std::move(objects[k]);
		theCapacity = newCapacity;
		std::swap(objects, newArray);
		delete[] newArray;
	}

	Object & operator[] (int index)
	{
		if (index < theCapacity) // index >= 0 && index < size()
			return objects[index];
	}
	const Object & operator[](int index) const
	{
		if (index < theCapacity)
			return objects[index];
	}

	bool empty() const { return size == 0; }
	int size() const { return theSize; }
	int capacity() const { return theCapacity; }

	void push_back(const Object & x)
	{
		if (theSize == theCapacity)
			reserve(2 * theCapacity + 1);
		objects[theSize++] = x;
	}
	void push_back(Object && x)
	{
		if (theSize == theCapacity)
			reserve(2 * theCapacity + 1);
		objects[theSize++] = std::move(x);
	}

	// 3-8
	void insert(int pos, const Object & x)
	{
		if (pos > theCapacity)
		{
			reserve(2 * theCapacity + 1);
			insert(pos, x);
		}
		if (pos >= theSize)
		{
			objects[pos] = x;
			++theSize;
		}
		else
		{
			Object * newArray = new Object[theCapacity];
			for (int k = 0; k < theSize; ++k)
			{
				if (k == pos)
					newArray[k] = x;
				else
					newArray[k] = std::move(objects[k+1]);
			}
			std::swap(objects, newArray);
			delete[] newArray;
			++theSize;
		}
	}

	void erase(int pos)
	{
		if (pos <= theSize)
		{
			Object * newArray = new Object[theCapacity];
			for (int k = 0; k < pos; ++k)
				newArray[k] = std::move(objects[k]);
			for (int k = pos; k < theSize; ++k)
				newArray[k] = objects[k + 1];
			std::swap(objects, newArray);
			--theSize;
		}

	}
	
	void pop_back() { --theSize; }

	const Object & back() const { return objects[theSize - 1]; }

	//typedef Object * iterator;
	//typedef const Object * const_iterator;

	//iterator begin() { return &objects[0]; }
	//const_iterator begin() const { return &objects[0]; }
	//iterator end() { return &objects[size()]; }
	//const_iterator end() const { return &objects[size()]; }

	static const int SPARE_CAPACITY = 16;

	// answers:
	iterator insert(iterator pos, const Object & x)
	{
		Object * iter = &objects[0];
		Object * oldArray = objects;
		++theSize;
		int i;
		if (theCapacity < theSize)
			theCapacity = theSize;
		objects = new Object[theCapacity];
		while (iter!=pos)
		{
			objects[i] = oldArray[i];
			iter += sizeof(Object);
			pos += sizeof(Object);
			++i;
		}
		objects[pos] = x;
		for (int k = post + 1; k < theSize; ++k)
			objects[k] = oldArray[k];
		delete[] oldArray;
		return &objects[pos];

	}

	// 3-10
	class const_iterator
	{
	public:
		const Object & operator* () const
		{
			return retrieve();
		}
		const_iterator & operator++ ()
		{
			++current;
			return *this;
		}
		const_iterator operator++ (int)
		{
			const_iterator old = *this;
			++(*this);
			return old;
		}
		bool operator== (const const_iterator & rhs) const
		{
			return current == rhs.current;
		}
		bool operator != (const const_iterator & rhs) const
		{
			return !(*this == rhs);
		}
	protected:
		Object *current;
		const Vector<Object> *theVect;
		Object & retrieve() const
		{
			assertIsValid();
			return *current;
		}
		const_iterator(const Vector<Object> & vect, Object *p)
			: theVect(& vect), current(p) {}
		void assertIsValid() const
		{
			if (theVect == NULL || current == NULL)
				throw IteratorOutofBoundException();
		}
		friend class Vector<Object>;
	};
	class itertor:public const_iterator
	{
	public:
		Object & operator* ()
		{
			return retrieve();
		}
		const Object & operator* () const
		{
			return const_iterator::operator*();
		}
		itertor & operator++ ()
		{
			++current;
			return *this;
		}
		itertor operator++ (int)
		{
			itertor old = *this;
			++(*this);
			return old;
		}
	protected:
		itertor(const Vector<Object> & vect, Object *p)
			: const_iterator(vect, p) { }
		friend class Vector<Object>;
	};
	itertor begin() { return itertor(*this, &objects[0]); }
	const_iterator begin() const { return const_iterator(*this, &objects[0]); }
	itertor end() { return itertor(*this, &objects[size()]); }
	const_iterator end() const { return const_iterator(*this, &objects[size()]); }
private:
	int theSize;
	int theCapacity;
	Object * objects;
};