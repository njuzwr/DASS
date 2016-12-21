#pragma once
#include <iostream>


template <typename Comparable>
class BinarySearchTree
{
public:
	BinarySearchTree();
	BinarySearchTree(const BinarySearchTree &rhs) : root(nullptr)
	{
		root = clone(rhs.root);
	}
	BinarySearchTree(BinarySearchTree && rhs);
	~BinarySearchTree()
	{
		makeEmpty();
	};

	const Comparable & findMin() const;
	const Comparable & findMax() const;
	bool contains(const Comparable & x) const
	{
		return contains(x, root);
	}
	bool isEmpty() const;
	void printTree(std::ostream & out = cout) const;

	void makeEmpty();
	void insert(const Comparable & x)
	{
		insert(x, root);
	}
	void insert(Comparable && x);
	void remove(const Comparable & x)
	{
		remove(x, root);
	}

	BinarySearchTree & operator=(const BinarySearchTree & rhs);
	BinarySearchTree & operator=(BinarySearchTree && rhs);

private:
	struct BinaryNode
	{
		Comparable element;
		BinaryNode *left;
		BinaryNode *right;

		BinaryNode(const Comparable & theElement, BinaryNode *lt, BinaryNode *rt)
			: element{ theElement }, left{ lt }, right{ rt } { }
		BinaryNode(Comparable && theElement, BinaryNode *lt, BinaryNode *rt)
			: element{ std::move(theElement) }, left{ lt }, right{ rt } { }
	};

	BinaryNode *root;

	void insert(const Comparable & x, BinaryNode * & t)
	{
	/* Internal method to insert into a subtree.
	 * x is the item to insert.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
	 */
		if (t == nullptr)
			t = new BinaryNode{ x, nullptr, nullptr };
		else if (x < t->element)
			insert(x, t->left);
		else if (t->element < x)
			insert(x, t->right);
		else
			;	// Duplicate, do nothing.
	}
	void insert(Comparable && x, BinaryNode * & t)
	{
	/* Intenal method to insert inot a subtree.
	 * x is the item to insert by moving.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
	 */
		if (t == nullptr)
			t = new BinaryNode{ std::move(x), nullptr, nullptr };
		else if (x < t->element)
			insert(std::move(x), t->left);
		else if (t->element < x)
			insert(std::move(x), t->right);
		else
			;	// Duplicate; do nothing
	}
	void remove(const Comparable & x, BinaryNode * & t)
	{
	/* Internal method to remove from a subtree.
	 * x is the item to remove.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
	 */
		if (t == nullptr)
			return;	// Item not found; do nothing
		if (x < t->element)
			remove(x, t->left);
		else if (t->element < x)
			remove(x, t->right);
		else if (t->left != nullptr && t->right != nullptr)	// Two children
		{
			t->element = findMin(t->right)->element;
			remove(t->element, t->right);
		}
		else
		{
			BinaryNode *oldNode = t;
			t = (t->left != nullptr) ? t->left : t->right;
			delete oldNode;
		}

	}
	BinaryNode * findMin(BinaryNode *t) const
	{
	/* Internal method to find the smallest item in a subtree t.
	 * Return node containing the smallest item.
	 * Do findMin recursively.
	 */
		if (t == nullptr)
			return nullptr;
		if (t->left == nullptr)
			return t;
		return findMin(t->left);
	}
	BinaryNode * findMax(BinaryNode *t) const
	{
	/* Internal method to find the largest item in a substree t.
	 * Return node containing the largest item.
	 * Do findMax nonrecursively.
	 */
	 	if (t != nullptr)
			while (t->right != nullptr)
				t = t->right;
		return t;
	}
	bool contains(const Comparable & x, BinaryNode *t) const
	{
		if (t == nullptr)
			return false;
		if (x < t->element)
			return contains(x, t->left);
		if (t->element < x)
			return contains(x, t->right);
		return true;	// Match
	}
	void makeEmpty(BinaryNode * & t)
	{
		if (t != nullptr)
		{
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		t = nullptr;
	}
	void printTree(BinaryNode *t, std::ostream & out) const;
	BinaryNode * clone(BinaryNode *t) const
	{
	// Internal method to clone subtree.
		if (t == nullptr)
			return nullptr;
		return new BinaryNode{ t->element, clone(t->left), clone(t->right) };
	}

};