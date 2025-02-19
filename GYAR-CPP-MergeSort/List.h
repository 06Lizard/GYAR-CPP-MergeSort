#pragma once
#include <iostream>
#include <string>
#include "Node.h"
#include "MergeSort.h"
#include "ParallellMergeSort.h"

template <typename T>
class List {
private:
	Node<T>* head; // ptr to the the first node
public:
	List()	//constructor of the list, will be empty
		: head(nullptr) // when list is constructed head is set to nullptr
	{ }
	List(T value)
		: head(new Node<T>(value))
	{ }

	// push to add object to list
	void push(T input) { // takes in a value as an input
		if (head == nullptr) // checks if theres no nodes in the list yet
		{
			head = new Node<T>(input); //	make a new node at head, sets the value of that node to the input
		}
		else {
			// a lot more optimized (fixed time to add elements now even)
			Node<T>* node = new Node<T>(input); // sets a pointer to the new node created
			node->next = head; // sets the new nodes next ptr to the head
			head = node; // makes the head node
			// this makes the new element be pushed at the start of the list instead of iterating though the entire list to the end just to add one element, taking more and more time the larger it gets
		}
		//else { // if there's already a node in the list then do this instead
		//	Node<T>* current = head; // set a pointer to where we're currently looking, starting at the heads position
		//	while (current->next != nullptr) { // while the next part in the list isn't null. in other words while there's an node after the current one
		//		current = current->next; //	the pointer "current" is switched from pointing at the current ellement we looked at to the next ellement
		//	}	// this repeats till the next element after the current is the last ellement shown by the current element pointing to a nullpointer
		//	current->next = new Node<T>(input);	// sets the current elements pointer to the next element (that we knew was a nullptr) point to a new Node witch will be the new last element in the list, pointing to a nullptr and having the value of the input
		//}
	}

	// push at index
	void pushAt(T input, int index) { // takes in an input for what we're gonna set the value of the new node too, and we'll take in an index for where we'll put the new node at
		if (index < 0 || index > getSize()) {	// checks if the index is to small or large
			std::cout << "Push index " << index << " out of range" << std::endl; // here we send an error to the console
			return; // here we return witch ends the execution of the code in this function right away 
		}

		Node<T>* push = new Node<T>(input); // make a pointer to a new node (that we make with the value of the input we took in) called push (cause it's what we're pushing in to the list)
		if (index == 0) {	// if the index we want to add stuff to is 0
			push->next = head; // take the new node we made called push and set it's pointer to the next ellement witch is originally nullptr point to the head of the list
			head = push; // make the pointer to the head of the list to push becuse push became the new head
			return; // end the function right here
		}
		Node<T>* current = head; // save a pointer for current node we're looking at in the list starting at head
		for (int i = 0; i < index - 1; i++) { // as long as i is smaller then the index minus one we'll execute the code in the loop and add one to i
			current = current->next; // eatch time this loop runs we move the pointer to the current element we're looking at to the next element in the list after that one
		} // when the loop as run we'll be at the position prior to were the new node will be
		push->next = current->next; // we move the pointer of the current's next to the push node's next
		current->next = push; // then we set the current next to the push node. this way we've effectivly made the next node after current become the new node and the node that previusly was after the current element is now being pointet to to the new node we put next to the current one
	}

	// pull takes number to for element x to get in list and returns it
	T pull(int index) { // takes in an index
		Node<T>* current = head; // makes a pointer to the current element we wanna be looking at and starts it at head
		for (int i = 0; i < index; i++) { // as long as i is smaller then the index minus one we'll execute the code in the loop and add one to i
			if (current->next == nullptr) // if the current nodes next pointer is pointing to a nullptr
				return NULL; // we return nothing becuse there's nothing at that index to return
			current = current->next; // if there is a node at the current's next we set the current to the currents next
		} // when this loop is done we'll be at the desired index in the list
		return current->value; // and we can now return the currents value
	}

	// remove will remove an object in list, takes in an int for with element it'll remove
	void removeElement(int index) { // takes in an index for what element we want to remove
		if (index < 0 || index > getSize() - 1) {	// checkes if the index is out of range by being to small or to large, we can't have an object before the position 0 nor after the max position, and cause we check the next position always it'll be the size-1
			std::cout << "Element index " << index << " out of range" << std::endl;	// gives back an error to the console
			return; // ends the function right ere
		}

		//remove			
		if (head == nullptr) // if the head is a nullptr we know the list is empty
			std::cout << "List is empty" << std::endl; // if list is empty, return a error to the console
		else if (index == 0) { // else if the list has ellements and the index we wanna remove is 0
			Node<T>* temp = head; // save a temporary pointer to the current head's possition
			head = head->next; // make the head's pointer point to the heads next element instead
			delete temp; // delete the old head that the temporary pointer was pointing too
		}
		else {	// otherwhise we'll do this instead
			Node<T>* current = head;	// makes a pointer to the current element we wanna be looking at and starts it at head 
			Node<T>* previus = nullptr;	// saves a pointer to the previus current, considering there's no previus current yet we set it to a nullptr
			for (int i = 0; i < index; i++) { // as long as i is smaller then the index minus one we'll execute the code in the loop and add one to i
				previus = current;	// set the previus pointers pointer to the current pointer
				current = current->next; // make the current pointer point to the curent pointer's next pointer that's pointing to the next element in the list
			}
			previus->next = current->next; // make the previus next point to the current's next
			delete current; // delete the element the current is pointing too
		}
	}

	// clear will remove all the ellements in the list...
	void clear() {
		while (head) { // while ther's a element
			Node<T>* current = head; // save the current first element
			head = head->next; // make the first element the second first element
			delete current; // delite the previously first element
		}
		head = nullptr; // set the current element to NULL
	}

	// get size
	int getSize() {
		Node<T>* current = head; // makes a pointer to the current element we wanna be looking at and starts it at head 
		int size = 0; // make an int to keep track of the size, starting it at 0		
		while (current) { // while the current isn't a nullptr
			size++; // we add one to the size
			current = current->next; // and we move the current to the next element
		}
		return size; // return the size as an int
	}

	// print element (input)
	void printElement(int index) { // we take in an index for what element we want to print in the list
		if (index < 0) { // if the index is less then zero
			std::cout << "index can't be negative" << std::endl; // send an error that the index is to small to the console
			return; // end the function right 'ere
		}
		if (head == nullptr) // if the list is empty, witch we check by looking at if the head is a nullptr
			std::cout << "List is empty" << std::endl; // we write in the console that the list is empty
		else { // otherwhise we'll do this 
			Node<T>* current = head; // makes a pointer to the current element we wanna be looking at and starts it at head 
			for (int i = 0; i < index; i++) { // as long as i is smaller then the index minus one we'll execute the code in the loop and add one to i
				if (current->next == nullptr) { // if the next element after the current one we're looking at is a nullptr
					std::cout << "Index " << index << " out of range" << std::endl; // write in the console that the index is out of range (it's to large)
					return; // end the function rigth 'ere
				}
				current = current->next; // make the current look at the next element instead
			}
			std::cout << "Element " << index << " value: " << current->value << std::endl; // print the element we wanted to print
		}
	}

	// print last element
	void printLast() {
		if (head) {
			Node<T>* current = head;
			while (current->next)
				current = current->next;
			std::cout << "Tail value: " << current->value << "\n";
		}
		else
			std::cout << "List is empty\n";
	}

	// print first element
	void printFirst() {
		if (head)
			std::cout << "Head value: " << head->value << "\n";
		else
			std::cout << "List is empty\n";
	}

	// print all
	void printAll() {
		if (head != nullptr) { // cehcks if there's any nodes in the list at all, if the head is a nullptr then it's empttry
			Node<T>* current = head;	// makes a pointer to the current element we wanna be looking at and starts it at head 
			while (current != nullptr) {	// while the current isn't nullptr, while the current element is a node and isn't nothing
				std::cout << current->value << std::endl;  // we'll write out the current element
				current = current->next; // then we'll make the curreent the next elmenet in the list
			}
		}
		else { // this is only acsesed if the list was empty
			std::cout << "List is empty" << std::endl; // so if the list was empty we write in to the console that the list was empty
		}
	}

	// sort list via bubble sort
	void boubbleSort() {
		int size = getSize();	// sets an int to keep track of the size of the list using the getSize() function. do this here instead of calling it in the foor loop multiple times
		if (size < 2) // if no or just 1 element
			return; // return cause list already sorted
		Node<T>* current; // makes a pointer to the current element we wanna be looking at
		T temporary; // initializes the temporary value so it dosn't get deconstructed and reconstructed every loop of the buble sort
		for (int i = 0; i < size - 1; i++) { // as long as i is smaller then the size minus one we'll execute the code in the loop and add one to i
			current = head; // sets the current to look at head witch is the start of the list
			for (int j = 0; j < size - i - 1; j++) { // as long as i is smaller then the index minus i minus one we'll execute the code in the loop and add one to i, reason we do size-i-1 is becuse i is the amount of elements we've already moved all the way to the right position, so we don't need to check our next elements to those positions again
				if (current->value > current->next->value) { // if the current value is larger then the next value from current
					// switch values
					temporary = current->value; // save a temporary variable for the value from current
					current->value = current->next->value; // set the current value to the next element after current 
					current->next->value = temporary; // then se the next elment after current to the temporary variable that we saved before
				}
				current = current->next; // then we move the current pointer to the next element
			}
		}
	}

	// merge sort the list
	void mergeSort() {
		//MergeSort<T> sort(head);		
		head = MergeSort::mergeSort<T>(head);
	}

	/*void parallellMergeSort() {
		ParallelMergeSort<T> sort(head, 4);
	}*/
};