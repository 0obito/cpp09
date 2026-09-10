#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <cstdlib>
#include <iostream>
#include <deque>

void myMergeInsertionSort(std::vector<int>& vecToSort, size_t callNumber, size_t numOfElements);
void myMergeInsertionSort(std::deque<int>& deqToSort, size_t callNumber, size_t numOfElements);
void printVec(const std::vector<int>& vec);
void printDeq(const std::deque<int>& deq);

#endif /*PMERGEME_HPP*/
