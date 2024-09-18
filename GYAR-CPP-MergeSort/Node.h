#pragma once
#include <string>

template<typename T>
class Node {
private:
public:
	// ptr to next
	Node<T>* next;
	// own value
	T value;

	Node(T input)	// constructor, needs value	
		: value(input), next(nullptr) // sets value to input and next to a nullptr
	{ }

	Node()	// constructor, no value
		: value(NULL), next(nullptr) // sets value to input and next to a nullptr
	{ }
};