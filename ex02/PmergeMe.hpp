#pragma once 

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <sys/time.h>

class PmergeMe
{
private:
    std::vector<int> _vec;
    std::deque<int> _deq;

    void mergeInsertionSort(std::vector<int>& container);
    void mergeInsertionSort(std::deque<int>& container);

    double nowMicros();

public:
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    void addNumber(const char* str);
    void execute();
};