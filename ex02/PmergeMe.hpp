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
    bool processLine(char *line);
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
    
    // Use insertion sort for small arrays
    if (n <= 10)
    {
        insertionSort(container, 0, n - 1);
        return;
    }

    // Create pairs and sort them
    size_t pairs = n / 2;
    for (size_t i = 0; i < pairs; ++i)
    {
        if (container[2 * i] > container[2 * i + 1])
        {
            std::swap(container[2 * i], container[2 * i + 1]);
        }
    }

    // Recursively sort the larger elements
    Container larger;
    for (size_t i = 0; i < pairs; ++i)
    {
        larger.push_back(container[2 * i + 1]);
    }
    
    if (larger.size() > 1)
        mergeInsertionSort(larger);

    // Build the result
    Container result;
    result.push_back(container[0]); // First smaller element
    
    for (size_t i = 0; i < larger.size(); ++i)
    {
        result.push_back(larger[i]);
    }

    // Insert remaining smaller elements using binary insertion
    for (size_t i = 1; i < pairs; ++i)
    {
        int value = container[2 * i];
        // Binary search for insertion position
        size_t left = 0;
        size_t right = result.size();
        while (left < right)
        {
            size_t mid = left + (right - left) / 2;
            if (result[mid] < value)
                left = mid + 1;
            else
                right = mid;
        }
        result.insert(result.begin() + left, value);
    }

    // Handle odd element if exists
    if (n % 2 == 1)
    {
        int value = container[n - 1];
        size_t left = 0;
        size_t right = result.size();
        while (left < right)
        {
            size_t mid = left + (right - left) / 2;
            if (result[mid] < value)
                left = mid + 1;
            else
                right = mid;
        }
        result.insert(result.begin() + left, value);
    }

    container = result;
}