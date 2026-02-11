#include "PmergeMe.hpp"

PmergeMe::PmergeMe( void ) {}

PmergeMe::~PmergeMe( void ) {}

double PmergeMe::nowMicros()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    return (tv.tv_sec * 1000000.0 + tv.tv_usec);
}


void PmergeMe::execute( void )
{
    std::cout << "Before: ";
    for (size_t i = 0; i < _values_vec.size(); ++i)
        std::cout << _values_vec[i] << " ";
    std::cout << "\n";

    double t1 = nowMicros();
    sort(_values_vec);
    double t2 = nowMicros();

    double t3 = nowMicros();
    sort(_values_deq);
    double t4 = nowMicros();

    std::cout << "After: ";
    for (size_t i = 0; i < _values_vec.size(); ++i)
        std::cout << _values_vec[i] << " ";
    std::cout << "\n";

    std::cout << "Time to process a range of " << _values_vec.size()
              << " elements with std::vector : " << (t2 - t1) << " us\n";
    std::cout << "Time to process a range of " << _values_deq.size()
              << " elements with std::deque  : " << (t4 - t3) << " us\n";
}

void PmergeMe::processLine(char *line)
{
    std::istringstream iss(line);
    std::string token;

    while (iss >> token)
    {
        for (size_t i = 0; i < token.size(); ++i)
        {
            if (!std::isdigit(token[i]))
                return (void)(std::cout << "Error: non-numeric token\n");
        }
        long n = std::strtol(token.c_str(), 0, 10);
        if (n < 0 || n > 2147483647)
            return (void)(std::cout << "Error: out of range\n");
        _values_vec.push_back(static_cast<int>(n));
        _values_deq.push_back(static_cast<int>(n));
    }
    if (_values_vec.empty() || _values_deq.empty())
        return (void)(std::cout << "Error: no numbers\n");
    std::cout << "befor : Vector ";
    for (size_t i = 0; i < _values_vec.size(); ++i)
        std::cout << _values_vec[i] << " ";
    std::cout << std::endl;
    std::cout << "befor : Deque ";
    for (size_t i = 0; i < _values_deq.size(); i++)
        std::cout << _values_deq[i] << " ";
    std::cout << std::endl;
    
}