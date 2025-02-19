#include <iostream>
#include <thread>
#include <chrono> // the system clock
#include <cstdlib> // for the rand and strand
#include <string>
#include "list.h"
#include "BenchmarkingTool.h"

void radix_byte_sort() {

    List<int> list;

    using Clock = std::chrono::high_resolution_clock;

    std::cout << "Enter the number of elements for each iteration: ";
    int numElements;
    std::cin >> numElements;
    std::cout << "Enter the number of forcedDouplets of eatch element (increases elements per iteration): ";
    int forcedDouplets;
    std::cin >> forcedDouplets;
    std::cout << "Enter the max value of the elements: ";
    int maxVal;
    std::cin >> maxVal;
    
    for (int i = 0; i < numElements; i++) {
        int randomValue = std::rand() % maxVal;
        for (int u = 0; u < forcedDouplets; u++)
            list.push(randomValue);
    }

    std::cout << "Sorting with Radix LSByte Sort...\n";
    auto start = Clock::now();
    list.radixSort_LSD();
    auto end = Clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;
    
    //display the tune it took to sort here as precisely as posible: 
    std::cout << "Time taken: " << duration.count() << " microsec (" 
              << duration.count() / 1000.0 << " ms)\n";

    std::cout << "Would you like to print the sorted list? (1 = Yes, 0 = No): ";
    bool write;
    std::cin >> write;
    if (write) {
        list.printAll();
    }
}


int main() {
    radix_byte_sort();

    //BenchmarkingTool benchmarking;
    //benchmarking.run();
}