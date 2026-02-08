#pragma once 


#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <chrono>
#include <iomanip>

class PmergeMe
{
    public:
        PmergeMe();
        ~PmergeMe();
        void processLine(char *line);
    private:
        std::vector<int> _vector;
        std::deque<int> _deque;
        // void mergeInsertSortVector(std::vector<int> &vec);
        // void mergeInsertSortDeque(std::deque<int> &deq);
        // void mergeVector(std::vector<int> &vec, int left, int mid, int right);
        // void mergeDeque(std::deque<int> &deq, int left, int mid, int right);
};