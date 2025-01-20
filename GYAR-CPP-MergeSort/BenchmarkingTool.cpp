#include "BenchmarkingTool.h"
#include <conio.h> // _getch(); (capture key presses)
#include <chrono>
#include <numeric>
#include <vector>
#include <thread>


void BenchmarkingTool::run()
{
    bool running = true;
    while (running) {
        printMenu();

        switch (navigateMenu()) {
        case 1:
            addRandomElements();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            break;
        case 2:
            addElement();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            break;
        case 3:
            removeElement();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            break;
        case 4:
            printElement();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            break;
        case 5:
            list.printAll();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            break;
        case 6:
            list.printFirst();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            break;
        case 7:
            list.printLast();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            break;
        case 8:
            list.boubbleSort();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            break;
        case 9:
            list.mergeSort();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            break;
        case 10:
            benchmarkSorts();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            break;
        case 11:
            running = false;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }

        std::cout << "\033[2J\033[1;1H";
    }
}

int BenchmarkingTool::navigateMenu()
{
    short selectedIndex = 1;
    while (true) 
    {
        updateMenu(selectedIndex);

        char key = _getch();

        switch (key) {
        case 'w': // 'w'
        case 72:  // ArrowUp
            selectedIndex = (selectedIndex <= 1) ? MenueItmesNum : --selectedIndex;
            break;

        case 's': // 's'
        case 80:  // ArrowDown
            selectedIndex = (selectedIndex >= MenueItmesNum) ? 1 : ++selectedIndex;
            break;

        case '\r': // Enter
            return selectedIndex;

        default:
            break;
        }
    }
}

void BenchmarkingTool::printMenu()
{
    std::cout << "\033[2J\033[1;1H"
        << "Menu:\n"
        << "\t Add x random elements with value between y and z\n"
        << "\t Add element\n"
        << "\t Remove element\n"
        << "\t Print element\n"
        << "\t Print all elements\n"
        << "\t Print first element\n"
        << "\t Print last element\n"
        << "\t Bubble sort\n"
        << "\t Merge sort\n"
        << "\t Benchmark bubble sort and merge sort (iterate x times with y elements each time)\n"
        << "\t Exit" << std::endl;
}

void BenchmarkingTool::updateMenu(short selectedIndex)
{    
    // clear prev
    for (int i = 1; i <= MenueItmesNum; ++i) {
        std::cout << "\033[" << i + 1 << ";1H   ";
    }

    // write selection arrow
    std::cout << "\033[" << selectedIndex + 1 << ";1H>> ";
}

void BenchmarkingTool::addRandomElements()
{
    std::cout << "\033[2J\033[1;1HNote: Only whole numbers allowed !\n"
        << "Enter the number of elements to add: ";
    int num;
    std::cin >> num;

    std::cout << "Enter the minimum value: ";
    int min;
    std::cin >> min;

    std::cout << "Enter the maximum value: ";
    int max;
    std::cin >> max;

    addRandomElements(num, min, max);
}

void BenchmarkingTool::addRandomElements(int num, int min, int max)
{
    for (int i = 0; i < num; i++) {
        int randomValue = (std::rand() % max) + min;
        list.push(randomValue);
    }
}

void BenchmarkingTool::addElement()
{    
    std::cout << "\033[2J\033[1;1HEnter the value to add: ";
    double value;
    std::cin >> value;
    list.push(value);
}

void BenchmarkingTool::removeElement()
{
    std::cout << "\033[2J\033[1;1HEnter the index of the element to remove: ";
    int index;
    std::cin >> index;
    list.removeElement(index);
}

void BenchmarkingTool::printElement()
{
    std::cout << "\033[2J\033[1;1HEnter the index of the element to print: ";
    int index;
    std::cin >> index;
    list.printElement(index);
}

void BenchmarkingTool::benchmarkSorts() {
    using Clock = std::chrono::high_resolution_clock;

    std::cout << "\033[2J\033[1;1HEnter the number of iterations: ";
    int iterations;
    std::cin >> iterations;

    std::cout << "Enter the number of elements for each iteration: ";
    int numElements;
    std::cin >> numElements;

    std::vector<double> mergeSortTimes;

    // benchmark merge sort
    for (int i = 0; i < iterations; ++i) {
        std::cout << "Initializing list for iteration " << i + 1 << "...\n";
        addRandomElements(numElements, 0, 10000);

        std::cout << "Sorting with Merge Sort...\n";
        auto start = Clock::now();
        list.mergeSort();
        auto end = Clock::now();

        std::chrono::duration<double, std::milli> duration = end - start;
        std::cout << "Iteration " << i + 1 << ": Merge Sort time = " << duration.count() << " ms\n";

        mergeSortTimes.push_back(duration.count());

        list.clear();
    }

    // calculate average merge sort thime
    double averageMergeSortTime = std::accumulate(mergeSortTimes.begin(), mergeSortTimes.end(), 0.0) / mergeSortTimes.size();
    std::cout << "\n\nAverage Merge Sort time: " << averageMergeSortTime << " ms";

    // benchmark bobble sort (single iteration)
    std::cout << "\nRunning a singular Boubble Sort iteration...";
    addRandomElements(numElements, 0, 10000);

    auto start = Clock::now();
    list.boubbleSort();
    auto end = Clock::now();

    std::chrono::duration<double> bubbleSortTime = end - start;
    if (bubbleSortTime.count() < 1)
        std::cout << "\nBubble Sort time: " << bubbleSortTime.count() * 1000 << " ms";
    else 
        std::cout << "\nBubble Sort time: " << bubbleSortTime.count() << " s";

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "\nPress 'Enter' to continue. ";
    while (true) { if (_getch() == '\r') break; }
}
