#pragma once
#include "Node.h"

//template <typename T>
class MergeSort {
//public:
//	MergeSort(Node<T>* &head) {
//		head = mergeSort(head);
//	}
//private:
public:
	template <typename T>
	static Node<T>* mergeSort(Node<T>* head) {
		//if (head == nullptr || head->next == nullptr) 
		if (!head || !head->next) // a bit faster and more optimized? just looks cleaner atleast, will have to check on larger scale		
			return head;

		Node<T>* mid = split(head);
		Node<T>* left = mergeSort(head);
		Node<T>* right = mergeSort(mid);

		return merge(left, right);
	}

private:
	template <typename T>
	static Node<T>* split(Node<T>* head) {
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

	template <typename T>
	static Node<T>* merge(Node<T>* left, Node<T>* right) // new merge that's actually iterative.
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




	//Node<T>* _merge(Node<T>* left, Node<T>* right) // this is a recersive merge witch I made first and has a multitude of drawbacks...
	//{
	//	if (left == nullptr) return right;
	//	if (right == nullptr) return left;
	//
	//	if (left->value < right->value) {
	//		left->next = _merge(left->next, right);
	//		return left;
	//	}
	//	else {
	//		right->next = _merge(left, right->next);
	//		return right;
	//	}
	//}
};