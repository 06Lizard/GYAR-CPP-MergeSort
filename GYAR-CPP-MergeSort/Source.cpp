#include <iostream>
#include <thread>
#include <chrono> // the system clock
#include <cstdlib> // for the rand and strand
#include <string>
#include "list.h"
#include "BenchmarkingTool.h"

int main() {
    BenchmarkingTool benchmarking;
    benchmarking.run();
}