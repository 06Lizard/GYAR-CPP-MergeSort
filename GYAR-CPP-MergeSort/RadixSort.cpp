#include "RadixSort.h"

void RadixSort::radixSort_LSB(Node<int>*& head) {
    if (!head || !head->next) return;

    int maxNum = head->value;
    for (Node<int>* curr = head; curr; curr = curr->next) {
        if (curr->value > maxNum) maxNum = curr->value;
    }
    int numBits = sizeof(int) * 8;

    for (int bit = 0; bit < numBits; ++bit) {
        head = bitwiseSort_LSB(head, bit);
    }
}

void RadixSort::radixSort_LSD(Node<int>*& head) {
    if (!head || !head->next) return;

    int largestNum = head->value;
    Node<int>* current = head;
    while (current) {
        if (current->value > largestNum) largestNum = current->value;
        current = current->next;
    }

    for (int exp = 1; largestNum / exp > 0; exp *= 10) {
        head = countingSort_LSD(head, exp);
    }
}

void RadixSort::radixSort_LSByte(Node<int>*& head) {
    if (!head || !head->next) return;

    const int BYTE_MASK = 0xFF; // 255, mask to extract 8-bit chunks
    const int BYTE_COUNT = sizeof(int); // 4 bytes in 32-bit int

    for (int byteIndex = 0; byteIndex < BYTE_COUNT; ++byteIndex) {
        head = countingSort_LSByte(head, byteIndex, BYTE_MASK);
    }
}

Node<int>* RadixSort::bitwiseSort_LSB(Node<int>* head, int bit) {
    Node<int>* zeroHead = nullptr, * zeroTail = nullptr;
    Node<int>* oneHead = nullptr, * oneTail = nullptr;

    for (Node<int>* curr = head; curr; ) {
        Node<int>* next = curr->next;
        if ((curr->value >> bit) & 1) {
            if (!oneHead) oneHead = oneTail = curr;
            else oneTail = oneTail->next = curr;
        }
        else {
            if (!zeroHead) zeroHead = zeroTail = curr;
            else zeroTail = zeroTail->next = curr;
        }
        curr = next;
    }

    if (zeroTail) zeroTail->next = oneHead;
    if (oneTail) oneTail->next = nullptr;

    return zeroHead ? zeroHead : oneHead;
}

Node<int>* RadixSort::countingSort_LSD(Node<int>* head, int exp) {
    Node<int>* buckets[10] = { nullptr };
    Node<int>* tails[10] = { nullptr };

    Node<int>* current = head;
    while (current) {
        int bucketIndex = (current->value / exp) % 10;
        if (!buckets[bucketIndex]) {
            buckets[bucketIndex] = tails[bucketIndex] = current;
        }
        else {
            tails[bucketIndex]->next = current;
            tails[bucketIndex] = current;
        }
        current = current->next;
    }

    Node<int>* newHead = nullptr, * newTail = nullptr;
    for (int i = 0; i < 10; i++) {
        if (buckets[i]) {
            if (!newHead) newHead = buckets[i];
            else newTail->next = buckets[i];
            newTail = tails[i];
        }
    }
    if (newTail) newTail->next = nullptr;

    return newHead;
}

Node<int>* RadixSort::countingSort_LSByte(Node<int>* head, int byteIndex, int BYTE_MASK) {
    Node<int>* buckets[256] = { nullptr };
    Node<int>* tails[256] = { nullptr };

    Node<int>* current = head;
    while (current) {
        int byteValue = (current->value >> (8 * byteIndex)) & BYTE_MASK;

        if (!buckets[byteValue]) {
            buckets[byteValue] = tails[byteValue] = current;
        }
        else {
            tails[byteValue]->next = current;
            tails[byteValue] = current;
        }
        current = current->next;
    }

    Node<int>* newHead = nullptr, * newTail = nullptr;
    for (int i = 0; i < 256; i++) {
        if (buckets[i]) {
            if (!newHead) newHead = buckets[i];
            else newTail->next = buckets[i];
            newTail = tails[i];
        }
    }

    if (newTail) newTail->next = nullptr;
    return newHead;
}