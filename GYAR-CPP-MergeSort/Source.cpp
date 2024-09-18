#include <iostream>
#include <thread>
#include <chrono> // the system clock
#include <cstdlib> // for the rand and strand
#include <string>
#include "list.h"

int main() {    
    std::chrono::high_resolution_clock::time_point start;
    std::chrono::high_resolution_clock::time_point end;
    std::chrono::duration<double> durationPrint;
    std::chrono::duration<double> durationRandom;
    std::chrono::duration<double> sortingDuration;
    std::chrono::duration<double> printDuration;

    List<int> list;
    int seed = 8;
    int numberOfElements = 10000;
    int maxNumberSize = 1000; // the maximum size is one smaller then this number


    // input random elements to list
    start = std::chrono::high_resolution_clock::now();
    std::srand(seed);
    for (int i = 0; i < numberOfElements; ++i) {
        // Generate a random number between 0 and 1000
        int randomValue = std::rand() % maxNumberSize;
        list.push(randomValue);                
    }
    end = std::chrono::high_resolution_clock::now();    
    durationRandom = end - start;

    //print unsorted list
    start = std::chrono::high_resolution_clock::now();
    //list.printAll();
    end = std::chrono::high_resolution_clock::now();
    durationPrint = end - start;    

    //std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    // the actual sorting of the list
    start = std::chrono::high_resolution_clock::now();
    list.mergeSort();
    //list.boubbleSort();
    end = std::chrono::high_resolution_clock::now();
    sortingDuration = (end - start)*1000; //miliseconds
    //sortingDuration = end - start; //seconds


    // print sorted list
    start = std::chrono::high_resolution_clock::now();
    //list.printAll();
    end = std::chrono::high_resolution_clock::now();
    printDuration = end - start;
    
    std::cout
        << "Number of elements: " << numberOfElements << "\n"
        << "Elements of size 0 to " << maxNumberSize - 1 << "\n"
        << "Time to load in random numbers to list was: " << durationRandom.count() << "s\n"
        << "Time to write out randomized list was: " << durationPrint.count() << "s\n"
        << "Time to print sorted list was: " << printDuration.count() << "s\n"
        << "Time to sort was: " << sortingDuration.count() << "ms\n"
        << std::endl;           
}

/// using namespace std::chrono_literals;
/// std::this_thread::sleep_for(1s);
/// std::this_thread::sleep_for(1000ms);
// std::this_thread::sleep_for(std::chrono::seconds(1));
// std::this_thread::sleep_for(std::chrono::milliseconds(1000));
// std::this_thread::sleep_for(std::chrono::duration<short, std::milli>(1000));