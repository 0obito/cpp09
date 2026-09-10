#include <cstdlib>
#include <iostream>
#include <vector>
#include <cerrno>
#include <climits>
#include <iomanip>
#include <sys/time.h>
#include <deque>
#include "PmergeMe.hpp"
#define MAX_ELEMENTS 100000

int main(int ac, char* av[]) {
    if (ac <= 1) {
        std::cerr << "Error: 0 elements were provided.\n";
        return 1;
    }
    if (ac == 2) {
        std::cerr << "Error: can't sort 1 element.\n";
        return 1;
    }

    size_t numOfElements = ac - 1;
    if (numOfElements > MAX_ELEMENTS) {
        std::cerr<<"Error: too many numbers.\n";
        std::cout<<"Note: since the subject demands a minimum of 3000 numbers, and to avoid any issues with the program, the maximum number of elements you can pass is " << MAX_ELEMENTS << "\n";
        return 1;
    }

    std::vector<int> intVec;
    intVec.reserve(numOfElements);
    std::deque<int> intDeq;

    char* endPtr;
    errno = 0;
    for (size_t i = 1; i <= numOfElements; i++) {
        long longElement = std::strtol(av[i], &endPtr, 10);
        if (errno == ERANGE) {
            if (longElement == LONG_MAX) {
                std::cerr << "Error: element " << i << " is too large (Overflow).\n";
            }
            else if (longElement == LONG_MIN) {
                std::cerr << "Error: element " << i << " is too small (Underflow).\n";
            }
            else {
                std::cerr << "Error: range issue occured.\n";
            }
            return 1;
        }
        if (av[i] == endPtr) {
            std::cerr << "Error: at element " << i << ", couldn't parse any digits.\n";
            return 1;
        }
        if (*endPtr != '\0') {
            std::cerr << "Error: at element " << i << ", trailing invalid characters.\n";
            return 1;
        }
        if (longElement > INT_MAX) {
            std::cerr << "Error: element " << i << " is too large (Overflow).\n";
            return 1;
        }
        if (longElement < INT_MIN) {
            std::cerr << "Error: element " << i << " is too small (Underflow).\n";
            return 1;
        }
        int intElement = static_cast<int>(longElement);
        intVec.push_back(intElement);
        intDeq.push_back(intElement);
    }

    std::cout << "Before:  ";
    printVec(intVec);

    // clock_t vecStartTime = clock();
    // myMergeInsertionSort(intVec, 0, numOfElements);
    // clock_t vecEndTime = clock();
    // double  vecTime = static_cast<double>(vecEndTime - vecStartTime) / CLOCKS_PER_SEC * 1000000.0;

    // clock_t deqStartTime = clock();
    // myMergeInsertionSort(intDeq, 0, numOfElements);
    // clock_t deqEndTime = clock();
    // double  deqTime = static_cast<double>(deqEndTime - deqStartTime) / CLOCKS_PER_SEC * 1000000.0;

    struct timeval vecStartTime, vecEndTime, deqStartTime, deqEndTime;

    gettimeofday(&vecStartTime, NULL);
    myMergeInsertionSort(intVec, 0, numOfElements);
    gettimeofday(&vecEndTime, NULL);
    double vecTime = (vecEndTime.tv_sec - vecStartTime.tv_sec) * 1000000.0 + (vecEndTime.tv_usec - vecStartTime.tv_usec);

    gettimeofday(&deqStartTime, NULL);
    myMergeInsertionSort(intDeq, 0, numOfElements);
    gettimeofday(&deqEndTime, NULL);
    double deqTime = (deqEndTime.tv_sec - deqStartTime.tv_sec) * 1000000.0 + (deqEndTime.tv_usec - deqStartTime.tv_usec);

    std::cout << "After:  ";
    printVec(intVec);

    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Time to process a range of " << numOfElements << " elements with std::vector : " << vecTime << " us\n";
    std::cout << "Time to process a range of " << numOfElements << " elements with std::deque : " << deqTime << " us\n";
    return 0;
}
