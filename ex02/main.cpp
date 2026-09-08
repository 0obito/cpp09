#include <cstdlib>
#include <iostream>
#include <vector>
#include <cerrno>
#include <climits>
#include "PmergeMe.hpp"

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
    std::cout<<"Number Of Passed Elements: "<<numOfElements<<"\n\n";
    std::vector<int> intVec;
    intVec.reserve(numOfElements);

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
    }

    myMergeInsertionSort(intVec, 0);

    //print size
    // std::cout<<"size = "<<intVec.size()<<"\n";

    // print vector
    // std::vector<int>::iterator it = intVec.begin();
    // for (;it < intVec.end(); it++) {
    //     std::cout << *it << "\n";
    // }

    return 0;
}
