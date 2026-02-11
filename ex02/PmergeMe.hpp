#pragma once 

#include <iostream>
#include <vector>
#include <deque>
#include <sys/time.h>
#include <algorithm>
#include <chrono>
#include <iomanip>

class PmergeMe
{
private:
    std::vector<int> _values_vec;
    std::deque<int> _values_deq;

    template <typename Container>
    void sort(Container& container);

    template <typename Container>
    void mergeInsertionSort(Container& container);

public:
    PmergeMe();
    ~PmergeMe();

    void execute();
    double nowMicros();
    void processLine(char *line);
};