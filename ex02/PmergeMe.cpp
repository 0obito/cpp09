#include "PmergeMe.hpp"

void printVec(const std::vector<int> &vec) {
    std::vector<int>::const_iterator it = vec.begin();
    for (; it != vec.end(); it++) {
        if (it != vec.begin()) {
            std::cout<<", ";
        }
        std::cout<<*it;
    }
    std::cout<<"\n";
}


void generateJacobsthalSeq(std::vector<size_t>& jacobSeq) {
    size_t prev = 1;
    size_t curr = 3;
    while (curr < 1500) {
        jacobSeq.push_back(curr);
        size_t next = curr + 2 * prev;
        prev = curr;
        curr = next;
    }
}

void mySwap(std::vector<int>& intVec, size_t distance, size_t firstIndex, size_t secondIndex) {
    for (size_t i = 0; i < distance; i++) {
        int temp = intVec[firstIndex - i];
        intVec[firstIndex - i] = intVec[secondIndex - i];
        intVec[secondIndex - i] = temp;
    }
}


size_t findInsertPosition(const std::vector<int>& mainChain, int pendingKey, size_t distance, size_t maxChunkCount) {
    size_t      low = 0;
    size_t      high = maxChunkCount;

    while (low < high) {
        size_t mid = low + (high - low) / 2;

        int midKey = mainChain[(mid * distance) + (distance - 1)];

        if (midKey < pendingKey) {
            low = mid + 1;
        }
        else {
            high = mid;
        }
    }

    return low;
}


void makeChains(size_t distance, std::vector<int>& vec, std::vector<int>& mainChain, std::vector<int>& pendingChain) {
    size_t                      losersTurn = 1;
    size_t                      chunkSize = distance;
    std::vector<int>::iterator  it = vec.begin();
    std::vector<int>::iterator  endIt = vec.end();

    mainChain.insert(mainChain.begin(), it, it + (chunkSize * 2));
    it += chunkSize * 2;
    while (it != endIt) {
        size_t chunkSize = (static_cast<size_t>(endIt - it) >= distance) ? distance : (endIt - it);
        if (losersTurn || chunkSize < distance) {
            pendingChain.insert(pendingChain.end(), it, it + chunkSize);
            losersTurn = 0;
        }
        else {
            mainChain.insert(mainChain.end(), it, it + chunkSize);
            losersTurn = 1;
        }
        it += chunkSize;
    }
}


std::vector<int> myMergeInsertionSort(std::vector<int>& vecToSort, size_t callNumber) {
    // SORTING PART
    size_t      distance = 1 << callNumber;              // the distance between elements to compare
    size_t      firstElementPos = distance;              //  at the start, the first element is located at distance
    size_t      firstIndex = firstElementPos - 1;        // 1st element index
    size_t      secondIndex = firstIndex + distance;     // 2nd element index
    while (secondIndex < vecToSort.size()) {
        if (vecToSort[firstIndex] > vecToSort[secondIndex]) {
            mySwap(vecToSort, distance, firstIndex, secondIndex);
        }
        firstIndex += (distance * 2);
        secondIndex += (distance * 2);
    }

    // RECURSIVE CALLS PART
    if (distance * 4 <= vecToSort.size())
        myMergeInsertionSort(vecToSort, callNumber + 1);

    // REST OF ALGORITHM
    std::vector<int>    mainChain;
    std::vector<int>    pendingChain;
    makeChains(distance, vecToSort, mainChain, pendingChain);
    std::vector<size_t> jacobSeq;
    generateJacobsSeq(std::vector<size_t>& jacobSeq);
    for (size_t i = 0; i < pendingChain.size(); i++) {
        int pendingKey = pendingChain[(i * distance) + (distance - 1)];
        size_t insertPos = findInsertPosition(mainChain, pendingKey, distance, maxChunkCount);
        mainChain.insert(mainChain.begin() + insertPos,);
    }

    // std::cout << "Vector for level " << callNumber << "\n";
    // printVec(vecToSort);
    // std::cout << "Main Chain for level " << callNumber << "\n";
    // printVec(mainChain);
    // std::cout << "Pending Chain for level " << callNumber << "\n";
    // printVec(pendingChain);
    // std::cout << "\n";

    return vecToSort;
}
