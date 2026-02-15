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

static std::vector<size_t> jacobsthalInsertionOrder(size_t count)
{
    std::vector<size_t> order;
    if (count <= 1)
        return order;

    std::vector<size_t> jacobsthal;
    jacobsthal.push_back(0);
    jacobsthal.push_back(1);
    while (jacobsthal.back() < count)
    {
        size_t next = jacobsthal[jacobsthal.size() - 1]
                    + 2 * jacobsthal[jacobsthal.size() - 2];
        jacobsthal.push_back(next);
    }
    size_t prev = 1;
    for (size_t k = 2; k < jacobsthal.size(); ++k)
    {
        size_t curr = jacobsthal[k];
        if (curr >= count)
            curr = count - 1;
        for (size_t i = curr; i >= prev && i > 0; --i)
        {
            order.push_back(i);
        }
        prev = curr + 1;
        if (prev >= count)
            break;
    }
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