#include "PmergeMe.hpp"

void myMergeInsertionSort(std::vector<int>& intVec) {
    std::map<int, int> winnersAndLosers;
    std::size_t i = 0;

    std::vector<int>::iterator vecItBeg = intVec.begin();
    std::vector<int>::iterator vecItEnd = intVec.end();
    for (; vecItBeg < vecItEnd - 1; vecItBeg++) {
        if (*vecItBeg > *(vecItBeg + 1)) {
            winnersAndLosers[*vecItBeg] = *(vecItBeg + 1);
        }
        // but how about duplicates? I feel they could be a problem
        else {
            winnersAndLosers[*(vecItBeg + 1)] = *vecItBeg;
        }
    }
}
