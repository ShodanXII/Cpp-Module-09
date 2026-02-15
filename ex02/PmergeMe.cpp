#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) : _vec(other._vec), _deq(other._deq) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    if (this != &other)
    {
        _vec = other._vec;
        _deq = other._deq;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

double PmergeMe::nowMicros()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000.0 + tv.tv_usec);
}

void PmergeMe::addNumber(const char* str)
{
    std::string token(str);

    if (token.empty())
    {
        std::cout << "Error" << std::endl;
        return;
    }

    for (size_t i = 0; i < token.size(); ++i)
    {
        if (!std::isdigit(token[i]))
        {
            std::cout << "Error" << std::endl;
            return;
        }
    }

    long n = std::strtol(token.c_str(), NULL, 10);
    if (n < 0 || n > 2147483647)
    {
        std::cout << "Error" << std::endl;
        return;
    }

    _vec.push_back(static_cast<int>(n));
    _deq.push_back(static_cast<int>(n));
}

static std::vector<size_t> jacobsthalInsertionOrder(size_t m)
{
    std::vector<size_t> order;
    if (m <= 2) {
        if (m == 2) order.push_back(1);
        return order;
    }

    size_t last = m - 1;
    std::vector<char> used(last + 1, 0);
    used[0] = 1;

    size_t j0 = 0, j1 = 1;
    while (true)
    {
        size_t j2 = j1 + 2 * j0;
        j0 = j1;
        j1 = j2;

        if (j1 > last) break;
        if (!used[j1]) {
            order.push_back(j1);
            used[j1] = 1;
        }
    }

    for (size_t k = 1; k <= last; ++k)
        if (!used[k]) order.push_back(k);

    return order;
}


void PmergeMe::mergeInsertionSort(std::vector<int>& container)
{
    if (container.size() <= 1)
        return;

    std::vector<std::pair<int, int> > pairs;
    int straggler = 0;
    bool hasStraggler = (container.size() % 2 != 0);

    for (size_t i = 0; i + 1 < container.size(); i += 2)
    {
        int a = container[i];
        int b = container[i + 1];
        if (a > b)
            pairs.push_back(std::make_pair(a, b));
        else
            pairs.push_back(std::make_pair(b, a));
    }
    if (hasStraggler)
        straggler = container[container.size() - 1];
    for (size_t i = 0; i < pairs.size(); ++i)
    {
        for (size_t j = i + 1; j < pairs.size(); ++j)
        {
            if (pairs[i].first > pairs[j].first)
                std::swap(pairs[i], pairs[j]);
        }
    }
    std::vector<int> mainChain;
    for (size_t i = 0; i < pairs.size(); ++i)
        mainChain.push_back(pairs[i].first);
    std::vector<int> losers;
    for (size_t i = 0; i < pairs.size(); ++i)
        losers.push_back(pairs[i].second);
    if (!losers.empty())
        mainChain.insert(mainChain.begin(), losers[0]);
    std::vector<size_t> insertOrder = jacobsthalInsertionOrder(losers.size());
    for (size_t i = 0; i < insertOrder.size(); ++i)
    {
        int toInsert = losers[insertOrder[i]];
        std::vector<int>::iterator pos = std::lower_bound(
            mainChain.begin(), mainChain.end(), toInsert);
        mainChain.insert(pos, toInsert);
    }
    if (hasStraggler)
    {
        std::vector<int>::iterator pos = std::lower_bound(
            mainChain.begin(), mainChain.end(), straggler);
        mainChain.insert(pos, straggler);
    }

    container = mainChain;
}

void PmergeMe::mergeInsertionSort(std::deque<int>& container)
{
    if (container.size() <= 1)
        return;

    std::vector<std::pair<int, int> > pairs;
    int straggler = 0;
    bool hasStraggler = (container.size() % 2 != 0);

    for (size_t i = 0; i + 1 < container.size(); i += 2)
    {
        int a = container[i];
        int b = container[i + 1];
        if (a > b)
            pairs.push_back(std::make_pair(a, b));
        else
            pairs.push_back(std::make_pair(b, a));
    }
    if (hasStraggler)
        straggler = container[container.size() - 1];

    for (size_t i = 0; i < pairs.size(); ++i)
    {
        for (size_t j = i + 1; j < pairs.size(); ++j)
        {
            if (pairs[i].first > pairs[j].first)
                std::swap(pairs[i], pairs[j]);
        }
    }
    std::deque<int> mainChain;
    for (size_t i = 0; i < pairs.size(); ++i)
        mainChain.push_back(pairs[i].first);

    std::vector<int> losers;
    for (size_t i = 0; i < pairs.size(); ++i)
        losers.push_back(pairs[i].second);

    if (!losers.empty())
        mainChain.insert(mainChain.begin(), losers[0]);

    std::vector<size_t> insertOrder = jacobsthalInsertionOrder(losers.size());
    for (size_t i = 0; i < insertOrder.size(); ++i)
    {
        int toInsert = losers[insertOrder[i]];
        std::deque<int>::iterator pos = std::lower_bound(
            mainChain.begin(), mainChain.end(), toInsert);
        mainChain.insert(pos, toInsert);
    }

    if (hasStraggler)
    {
        std::deque<int>::iterator pos = std::lower_bound(
            mainChain.begin(), mainChain.end(), straggler);
        mainChain.insert(pos, straggler);
    }

    container = mainChain;
}

void PmergeMe::execute()
{
    if (_vec.empty())
    {
        std::cout << "Error" << std::endl;
        return;
    }
    std::cout << "Before:";
    for (size_t i = 0; i < _vec.size(); ++i)
        std::cout << " " << _vec[i];
    std::cout << std::endl;
    double t1 = nowMicros();
    mergeInsertionSort(_vec);
    double t2 = nowMicros();
    double t3 = nowMicros();
    mergeInsertionSort(_deq);
    double t4 = nowMicros();
    std::cout << "After:";
    for (size_t i = 0; i < _vec.size(); ++i)
        std::cout << " " << _vec[i];
    std::cout << std::endl;

    std::cout << "Time to process a range of " << _vec.size()
              << " elements with std::vector : " << std::fixed
              << std::setprecision(5) << (t2 - t1) << " us" << std::endl;
    std::cout << "Time to process a range of " << _deq.size()
              << " elements with std::deque  : " << std::fixed
              << std::setprecision(5) << (t4 - t3) << " us" << std::endl;
}