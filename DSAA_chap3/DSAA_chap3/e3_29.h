#pragma once
// Assuming no header and that first is not nullptr
template <typename T>
struct Node
{
	T data;
	Node * next;
};
template <typename T>
Node<T> *reverseList (Node<T> *first)
{
	Node<T> * currentPos, *nextPos, *previousPos;
	previousPos = nullptr;
	currentPos = first;
	nextPos = first->next;
	while(nextPos != nullptr)
	{
		currentPos->next = previousPos;
		previousPos = currentPos;
		currentPos = nextPos;
		nextPos = nextPos->next;
	}
	currentPos->next = previousPos;
	return currentPos;
}