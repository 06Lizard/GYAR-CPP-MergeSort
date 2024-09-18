#pragma once
#include <iostream>
#include <string>
#include "Node.h"

template <typename T>
class List {
private:
	Node<T>* head; // ptr to the the first node
public:
	List()	//constructor of the list, will be empty
		: head(nullptr) // when list is constructed head is set to nullptr
	{ }

	// push to add object to list
	void push(T input) { // takes in a value as an input
		if (head == nullptr) // checks if theres no nodes in the list yet
		{
			head = new Node<T>(input); //	make a new node at head, sets the value of that node to the input
		}
		else { // if there's already a node in the list then do this instead
			Node<T>* current = head; // set a pointer to where we're currently looking, starting at the heads position
			while (current->next != nullptr) { // while the next part in the list isn't null. in other words while there's an node after the current one
				current = current->next; //	the pointer "current" is switched from pointing at the current ellement we looked at to the next ellement
			}	// this repeats till the next element after the current is the last ellement shown by the current element pointing to a nullpointer
			current->next = new Node<T>(input);	// sets the current elements pointer to the next element (that we knew was a nullptr) point to a new Node witch will be the new last element in the list, pointing to a nullptr and having the value of the input
		}
	}

	// push at index
	void pushAt(T input, int index) { // takes in an input for what we're gonna set the value of the new node too, and we'll take in an index for where we'll put the new node at
		if (index < 0 || index > getSize()) {	// checks if the index is to small or large
			std::cout << "Push index " << index << " out of range" << std::endl; // here we send an error to the console
			return; // here we return witch ends the execution of the code in this function right away 
		}

		Node<T>* push = new Node<T>(input); // make a pointer to a new node (that we make with the value of the input we took in) called push (cause it's what we're pushing in to the list)
		Node<T>* current = head; // save a pointer for current node we're looking at in the list starting at head
		if (index == 0) {	// if the index we want to add stuff to is 0
			push->next = head; // take the new node we made called push and set it's pointer to the next ellement witch is originally nullptr point to the head of the list
			head = push; // make the pointer to the head of the list to push becuse push became the new head
			return; // end the function right here
		}
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

	// get size
	int getSize() {
		Node<T>* current = head; // makes a pointer to the current element we wanna be looking at and starts it at head 
		int size = 0; // make an int to keep track of the size, starting it at 0
		while (current != nullptr) { // while the current isn't a nullptr
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
		printElement(getSize() - 1); // call the printElement function and puts in the index size -1 using the getSize function. this prints the last element in the list to the console
	}

	// print first element
	void printFirst() {
		printElement(0); // call the printElement function and puts in the index 0 witch is always the first element
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
		Node<T>* current = head; // makes a pointer to the current element we wanna be looking at and starts it at head 

		for (int i = 0; i < size - 1; i++) { // as long as i is smaller then the size minus one we'll execute the code in the loop and add one to i
			current = head; // sets the current to head witch is the start of the list
			for (int j = 0; j < size - i - 1; j++) { // as long as i is smaller then the index minus i minus one we'll execute the code in the loop and add one to i, reason we do size-i-1 is becuse i is the amount of elements we've already moved all the way to the right position, so we don't need to check our next elements to those positions again
				if (current->value > current->next->value) { // if the current value is larger then the next value from current
					// switch values
					T temporary = current->value; // save a temporary variable for the value from current
					current->value = current->next->value; // set the current value to the next element after current 
					current->next->value = temporary; // then se the next elment after current to the temporary variable that we saved before
				}
				current = current->next; // then we move the current pointer to the next element
			}
		}
	}

	// merge sort the list
	void mergeSort() {
		head = mergeSort(head);
	}

private:
	Node<T>* mergeSort(Node<T>* head) {
		//if (head == nullptr || head->next == nullptr) 
		if (!head || !head->next) // a bit faster and more optimized? just looks cleaner atleast, will have to check on larger scale
		{
			return head;
		}

		Node<T>* mid = split(head);
		Node<T>* left = mergeSort(head);
		Node<T>* right = mergeSort(mid);

		return merge(left, right);
	}

	Node<T>* split(Node<T>* head) {
//		if (head == nullptr || head->next == nullptr) {							// neccesery?
//			return nullptr;														// like didn't we just check that in Node* mergeSort 
//		}																						// Yes we did
		Node<T>* slow = head;
		Node<T>* fast = head->next;

		//while (fast != nullptr && fast->next != nullptr)
		while (fast && fast->next) // might be a slight bit faster, looks cleaner
		{
			slow = slow->next;
			fast = fast->next->next;
		}

		Node<T>* mid = slow->next;
		slow->next = nullptr;
		return mid;
	}

	Node<T>* merge(Node<T>* left, Node<T>* right) // new merge that's actually iterative.
	{
		//if (left == nullptr) return right;			//not sure if needed
		//if (right == nullptr) return left;			// nor this

		// Head of merging 
		//Node<T>* mergedHead = nullptr; // better to run tmp?
		Node<T>* tmp = new Node<T>(); // tmp

		// Pointer to track the end of the merged list
		//Node<T>* tail = nullptr;
		Node<T>* tail = tmp; // tmp

		// Initialize mergedHead and tail to the smallest first node, would be removed if merge head
		//if (left->value < right->value) {
		//	mergedHead = left;
		//	tail = left;
		//	left = left->next;
		//}
		//else {
		//	mergedHead = right;
		//	tail = right;
		//	right = right->next;
		//}

		// Merge the two lists in place
		//while (left != nullptr && right != nullptr) 
		while (left && right) // might be slightly faster, looks cleaner
		{
			if (left->value < right->value) 
			{
				tail->next = left;
				left = left->next;
			}
			else 
			{
				tail->next = right;
				right = right->next;
			}
			tail = tail->next;
		}

		// Attach the remaining elements of whichever list is non-empty
		//tail->next = (left != nullptr) ? left : right;
		tail->next = (left) ? left : right; //  might be slightly more optimised

		//Node<T>* mergedHead = tmp->next;
		//delete tmp;
		/// or
		return tmp->next; ///????
		//return mergedHead;
	}





	Node<T>* _merge(Node<T>* left, Node<T>* right) // this is a recersive merge witch I made first and has a multitude of drawbacks...
	{ 
		if (left == nullptr) return right;
		if (right == nullptr) return left;

		if (left->value < right->value) {
			left->next = _merge(left->next, right);
			return left;
		}
		else {
			right->next = _merge(left, right->next);
			return right;
		}
	}
};