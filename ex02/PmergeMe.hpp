#pragma once 

#include <iostream>
#include <vector>
#include <deque>
#include <sys/time.h>
#include <algorithm>
#include <sstream>
#include <cstdlib>
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

    template <typename Container>
    void insertionSort(Container& container, size_t left, size_t right);

public:
    PmergeMe();
    ~PmergeMe();

    void execute();
    double nowMicros();
    bool processLine(const char *line);
};

// Template implementations must be in header file

template <typename Container>
void PmergeMe::sort(Container& container)
{
    if (container.size() <= 1)
        return;
    mergeInsertionSort(container);
}

template <typename Container>
void PmergeMe::insertionSort(Container& container, size_t left, size_t right)
{
    for (size_t i = left + 1; i <= right; ++i)
    {
        int key = container[i];
        size_t j = i;
        while (j > left && container[j - 1] > key)
        {
            container[j] = container[j - 1];
            --j;
        }
        container[j] = key;
    }
}

template <typename Container>
void PmergeMe::mergeInsertionSort(Container& container)
{
    size_t n = container.size();
    
    // Use insertion sort for small arrays (threshold)
    if (n <= 16)
    {
        insertionSort(container, 0, n - 1);
        return;
    }

    // Simple merge-insertion: recursively sort, then use binary insertion
    // Split into two halves
    size_t mid = n / 2;
    Container left, right;
    
    for (size_t i = 0; i < mid; ++i)
        left.push_back(container[i]);
    for (size_t i = mid; i < n; ++i)
        right.push_back(container[i]);
    
    // Recursively sort both halves
    mergeInsertionSort(left);
    mergeInsertionSort(right);
    
    // Merge using binary insertion
    Container result = left;
    for (size_t i = 0; i < right.size(); ++i)
    {
        typename Container::iterator pos = std::lower_bound(result.begin(), result.end(), right[i]);
        result.insert(pos, right[i]);
    }
    
    container = result;
}