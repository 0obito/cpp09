#include "PmergeMe.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  STD::VECTOR
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void printVec(const std::vector<int>& vec) {
    std::vector<int>::const_iterator it = vec.begin();
    for (; it != vec.end(); it++) {
        if (it != vec.begin()) {
            std::cout<<" ";
        }
        std::cout<<*it;
    }
    std::cout<<"\n";
}


void generateJacobsSeq(std::vector<size_t>& jacobSeq, size_t numOfElements) {
    size_t prev = 1;
    size_t curr = 3;
    while (curr <= numOfElements) {
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


void makeChains(size_t distance, std::vector<int>& vec, std::vector<int>& mainChain, std::vector<int>& pendingChain, std::vector<int>& leftChain) {
    size_t                      pairSize = distance * 2;
    std::vector<int>::iterator  it = vec.begin();
    std::vector<int>::iterator  endIt = vec.end();

    mainChain.insert(mainChain.begin(), it, it + pairSize);
    it += pairSize;
    while (it != endIt) {
        size_t chunkSize = (static_cast<size_t>(endIt - it) >= pairSize) ? pairSize : (endIt - it);
        if (chunkSize < pairSize) {
            if (chunkSize == pairSize / 2) {
                pendingChain.insert(pendingChain.end(), it, it + pairSize / 2);
            }
            else if (chunkSize > pairSize / 2) {
                pendingChain.insert(pendingChain.end(), it, it + pairSize / 2);
                leftChain.insert(leftChain.end(), it + pairSize / 2, it + chunkSize);
            }
            else {
                leftChain.insert(leftChain.end(), it, it + chunkSize);
            }
        }
        else {
            pendingChain.insert(pendingChain.end(), it, it + chunkSize / 2);
            mainChain.insert(mainChain.end(), it + chunkSize / 2, it + chunkSize);
        }
        it += chunkSize;
    }
}


int insertChunkToMainChain(std::vector<int>& mainChain, const std::vector<int>& pendingChain, size_t lastJacobs, size_t currentJacobs, size_t distance) {
    int     startIndex = currentJacobs - 2;
    int     endIndex = lastJacobs - 1;
    bool    noIndexCorrespond = (endIndex * distance) + (distance - 1) < pendingChain.size() ? false : true;

    if (noIndexCorrespond) {
        return 1;
    }

    for (;startIndex >= endIndex; startIndex--) {
        int     pendingChunkIndex = (startIndex * distance) + (distance - 1) < pendingChain.size() ? (startIndex * distance) + (distance - 1) : -1;
        if (pendingChunkIndex == -1) {
            continue ;
        }
        int     pendingChunkKey = pendingChain[pendingChunkIndex];
        size_t  insertPos  = findInsertPosition(mainChain, pendingChunkKey, distance, mainChain.size() / distance);
        mainChain.insert(mainChain.begin() + (insertPos * distance), pendingChain.begin() + (startIndex * distance), pendingChain.begin() + pendingChunkIndex + 1);
    }

    return 0;
}


void myMergeInsertionSort(std::vector<int>& vecToSort, size_t callNumber, size_t numOfElements) {
    size_t      distance = 1 << callNumber;
    size_t      firstElementPos = distance;
    size_t      firstIndex = firstElementPos - 1;
    size_t      secondIndex = firstIndex + distance;

    while (secondIndex < vecToSort.size()) {
        if (vecToSort[firstIndex] > vecToSort[secondIndex]) {
            mySwap(vecToSort, distance, firstIndex, secondIndex);
        }
        firstIndex += (distance * 2);
        secondIndex += (distance * 2);
    }

    if (distance * 4 <= vecToSort.size())
        myMergeInsertionSort(vecToSort, callNumber + 1, numOfElements);

    std::vector<int>    mainChain;
    std::vector<int>    pendingChain;
    std::vector<int>    leftChain;
    makeChains(distance, vecToSort, mainChain, pendingChain, leftChain);

    std::vector<size_t> jacobSeq;
    generateJacobsSeq(jacobSeq, numOfElements);
    size_t  lastJacobs = 1;
    std::vector<size_t>::iterator currentJacobs = jacobSeq.begin();

    while (currentJacobs != jacobSeq.end() && insertChunkToMainChain(mainChain, pendingChain, lastJacobs, *currentJacobs, distance) == 0) {
        lastJacobs = *currentJacobs;
        currentJacobs++;
    }

    if (!leftChain.empty()) {
        mainChain.insert(mainChain.end(), leftChain.begin(), leftChain.end());
    }

    vecToSort = mainChain;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  STD::DEQUE
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void printDeq(const std::deque<int>& deq) {
    std::deque<int>::const_iterator it = deq.begin();
    for (; it != deq.end(); it++) {
        if (it != deq.begin()) {
            std::cout<<" ";
        }
        std::cout<<*it;
    }
    std::cout<<"\n";
}


void generateJacobsSeq(std::deque<size_t>& jacobSeq, size_t numOfElements) {
    size_t prev = 1;
    size_t curr = 3;
    while (curr <= numOfElements) {
        jacobSeq.push_back(curr);
        size_t next = curr + 2 * prev;
        prev = curr;
        curr = next;
    }
}


void mySwap(std::deque<int>& intDeq, size_t distance, size_t firstIndex, size_t secondIndex) {
    for (size_t i = 0; i < distance; i++) {
        int temp = intDeq[firstIndex - i];
        intDeq[firstIndex - i] = intDeq[secondIndex - i];
        intDeq[secondIndex - i] = temp;
    }
}


size_t findInsertPosition(const std::deque<int>& mainChain, int pendingKey, size_t distance, size_t maxChunkCount) {
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


void makeChains(size_t distance, std::deque<int>& deq, std::deque<int>& mainChain, std::deque<int>& pendingChain, std::deque<int>& leftChain) {
    size_t                      pairSize = distance * 2;
    std::deque<int>::iterator   it = deq.begin();
    std::deque<int>::iterator   endIt = deq.end();

    mainChain.insert(mainChain.begin(), it, it + pairSize);
    it += pairSize;
    while (it != endIt) {
        size_t chunkSize = (static_cast<size_t>(endIt - it) >= pairSize) ? pairSize : (endIt - it);
        if (chunkSize < pairSize) {
            if (chunkSize == pairSize / 2) {
                pendingChain.insert(pendingChain.end(), it, it + pairSize / 2);
            }
            else if (chunkSize > pairSize / 2) {
                pendingChain.insert(pendingChain.end(), it, it + pairSize / 2);
                leftChain.insert(leftChain.end(), it + pairSize / 2, it + chunkSize);
            }
            else {
                leftChain.insert(leftChain.end(), it, it + chunkSize);
            }
        }
        else {
            pendingChain.insert(pendingChain.end(), it, it + chunkSize / 2);
            mainChain.insert(mainChain.end(), it + chunkSize / 2, it + chunkSize);
        }
        it += chunkSize;
    }
}


int insertChunkToMainChain(std::deque<int>& mainChain, const std::deque<int>& pendingChain, size_t lastJacobs, size_t currentJacobs, size_t distance) {
    int     startIndex = currentJacobs - 2;
    int     endIndex = lastJacobs - 1;
    bool    noIndexCorrespond = (endIndex * distance) + (distance - 1) < pendingChain.size() ? false : true;

    if (noIndexCorrespond) {
        return 1;
    }

    for (;startIndex >= endIndex; startIndex--) {
        int     pendingChunkIndex = (startIndex * distance) + (distance - 1) < pendingChain.size() ? (startIndex * distance) + (distance - 1) : -1;
        if (pendingChunkIndex == -1) {
            continue ;
        }
        int     pendingChunkKey = pendingChain[pendingChunkIndex];
        size_t  insertPos  = findInsertPosition(mainChain, pendingChunkKey, distance, mainChain.size() / distance);
        mainChain.insert(mainChain.begin() + (insertPos * distance), pendingChain.begin() + (startIndex * distance), pendingChain.begin() + pendingChunkIndex + 1);
    }

    return 0;
}


void myMergeInsertionSort(std::deque<int>& deqToSort, size_t callNumber, size_t numOfElements) {
    size_t      distance = 1 << callNumber;
    size_t      firstElementPos = distance;
    size_t      firstIndex = firstElementPos - 1;
    size_t      secondIndex = firstIndex + distance;

    while (secondIndex < deqToSort.size()) {
        if (deqToSort[firstIndex] > deqToSort[secondIndex]) {
            mySwap(deqToSort, distance, firstIndex, secondIndex);
        }
        firstIndex += (distance * 2);
        secondIndex += (distance * 2);
    }

    if (distance * 4 <= deqToSort.size())
        myMergeInsertionSort(deqToSort, callNumber + 1, numOfElements);

    std::deque<int>    mainChain;
    std::deque<int>    pendingChain;
    std::deque<int>    leftChain;
    makeChains(distance, deqToSort, mainChain, pendingChain, leftChain);

    std::deque<size_t> jacobSeq;
    generateJacobsSeq(jacobSeq, numOfElements);
    size_t  lastJacobs = 1;
    std::deque<size_t>::iterator currentJacobs = jacobSeq.begin();

    while (currentJacobs != jacobSeq.end() && insertChunkToMainChain(mainChain, pendingChain, lastJacobs, *currentJacobs, distance) == 0) {
        lastJacobs = *currentJacobs;
        currentJacobs++;
    }

    if (!leftChain.empty()) {
        mainChain.insert(mainChain.end(), leftChain.begin(), leftChain.end());
    }

    deqToSort = mainChain;
}
