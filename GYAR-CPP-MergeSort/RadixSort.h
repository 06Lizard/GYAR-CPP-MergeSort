#pragma once
#include "Node.h"

/// <summary>
/// RadixSort is a fast and effichent sorting algoritm however with some limitations.
/// It can only handle intigers as decimals/floating-points and negative numbers screw it over.
/// LSB starts at the least significant bit and works up to the most significant bit.
/// LSD starts at the least significant digit and works up to the most significant digit.
/// LSByte starts at the least significant byte and works up to the most significant byte.
/// 
/// LSB becomes the slowest becuse of how fiew buckets there are and number of bytes we have to do 8 pases for every byte.
/// LSD is good but needs the cpu to parse the bits into numbers and then push it into the corect bucket.
/// LSByte should be the most optimized as it takes in a whole byte at a time witch is the maximum set the cpu can handle at once.
/// </summary>
class RadixSort {
public:
    static void radixSort_LSB(Node<int>*& head);
    static void radixSort_LSD(Node<int>*& head);
    static void radixSort_LSByte(Node<int>*& head);

private:
    static Node<int>* bitwiseSort_LSB(Node<int>* head, int bit);
    static Node<int>* countingSort_LSD(Node<int>* head, int exp);
    static Node<int>* countingSort_LSByte(Node<int>*head, int byteIndex, int BYTE_MASK);
};
