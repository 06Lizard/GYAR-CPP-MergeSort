#pragma once
#include "Node.h"
#include "ThreadPool.h"

template <typename T>
class ParallelMergeSort {
public:
	// Constructor starts the sorting process immediately
	ParallelMergeSort(Node<T>*& head, int threads) : threadPool(threads) {
		head = parallelMergeSort(head);
	}

private:
	ThreadPool threadPool;

	Node<T>* parallelMergeSort(Node<T>* head) {
		if (!head || !head->next)
			return head;

		Node<T>* mid = split(head);

		// Enqueue left and right splits to the left/right stack
		auto left = threadPool.enqueueLeftRight(&ParallelMergeSort::parallelMergeSort, this, head);
		auto right = threadPool.enqueueLeftRight(&ParallelMergeSort::parallelMergeSort, this, mid);

		// Enqueue merge operation in the merge stack, waiting for left and right to finish
		return threadPool.enqueueMerge(&ParallelMergeSort::merge, this, left.get(), right.get()).get();
	}

	Node<T>* split(Node<T>* head) {
		Node<T>* slow = head;
		Node<T>* fast = head->next;

		while (fast && fast->next) {
			slow = slow->next;
			fast = fast->next->next;
		}

		Node<T>* mid = slow->next;
		slow->next = nullptr;
		return mid;
	}

	Node<T>* merge(Node<T>* left, Node<T>* right) {
		Node<T>* tmp = new Node<T>();
		Node<T>* tail = tmp;

		while (left && right) {
			if (left->value < right->value) {
				tail->next = left;
				left = left->next;
			}
			else {
				tail->next = right;
				right = right->next;
			}
			tail = tail->next;
		}

		tail->next = (left) ? left : right;
		return tmp->next;
	}
};