#include "PmergeMe.hpp"

void mySwap(std::vector<int>& intVec, size_t distance, size_t firstIndex, size_t secondIndex) {
    for (size_t i = 0; i < distance; i++) {
        int temp = intVec[firstIndex - i];
        intVec[firstIndex - i] = intVec[secondIndex - i];
        intVec[secondIndex - i] = temp;
    }
}


std::vector<int> myMergeInsertionSort(std::vector<int>& vecToSort, size_t callNumber) {

    // std::vector<int> copy = vecToSort;

    // SORTING PART
        //   i < vec.size() because we compare elemnt at idx = i vs element at idx = i + 1
        //     not sure the loop condition is correct for recursive calls, shall check it later

    size_t distance = 1 << callNumber;              // the distance between elements to compare
    size_t firstElementPos = distance;              //  at the start, the first element is located at distance
    size_t firstIndex = firstElementPos - 1;        // 1st element index
    size_t secondIndex = firstIndex + distance;     // 2nd element index
    while (secondIndex < vecToSort.size()) {
        if (vecToSort[firstIndex] > vecToSort[secondIndex]) {
            mySwap(vecToSort, distance, firstIndex, secondIndex);
        }
        firstIndex += (distance * 2);
        secondIndex += (distance * 2);
    }

    // PRINTING CURRENT STATE
    std::size_t                 braceIndex = 1;
    std::size_t                 vecSize = vecToSort.size();
    std::vector<int>::iterator  it = vecToSort.begin();

    std::cout << "====================== AT CALL NUMBER: " << callNumber << " =================\n";
    for (;it < vecToSort.end(); it++) {
        if (braceIndex == 1) {
            std::cout<<"[";
        }
        else if (braceIndex == vecSize) {
            std::cout << ", " << *it;
            std::cout<<"]";
            break ;
        }
        else if (!((braceIndex - 1) % (distance * 2))) {
            std::cout<<"] [";
        }
        else {
            std::cout<<", ";
        }
        std::cout << *it;
        braceIndex++;
    }
    std::cout << "\n----------------------------------------------------\n\n";

    // RECURSIVE CALLS PART
    if (distance * 4 <= vecToSort.size())
        myMergeInsertionSort(vecToSort, callNumber + 1);



    // // PRINTING PART (BEFORE AND AFTER)
    // std::cout << "====================== AT ENTRY: " << callNumber << " =================\n";
    // std::cout << "BEFORE:\n";
    // it = copy.begin();
    // for (;it < copy.end(); it++) {
    //     std::cout << *it;
    //     if (it < copy.end() - 1)
    //         std::cout<<", ";
    // }
    // std::cout << "\n----------------------------------------------------\n";

    // std::cout << "AFTER:\n";
    // it = vecToSort.begin();
    // for (;it < vecToSort.end(); it++) {
    //     std::cout << *it;
    //     if (it < vecToSort.end() - 1)
    //         std::cout<<", ";
    // }
    // std::cout << "\n====================================================\n\n\n\n";

    // REST OF ALGORITHM
    // ...
    // .....
    // .......

    return vecToSort;
}
