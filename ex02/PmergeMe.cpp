#include "PmergeMe.hpp"

PmergeMe::PmergeMe( void ) {}

PmergeMe::~PmergeMe( void ) {}

int valid(std::string line) // parsing the input 
{
    for (size_t i = 0; i < line.size(); i++)
        
}

void PmergeMe::processLine(char *line)
{
    std::istringstream iss(line);
    std::vector<int> values;
    std::string token;

    while (iss >> token)
    {
        // basic numeric check
        for (size_t i = 0; i < token.size(); ++i)
        {
            if (!std::isdigit(token[i]))
                return (void)(std::cout << "Error: non-numeric token\n");
        }

        long n = std::strtol(token.c_str(), 0, 10);
        if (n < 0 || n > 2147483647)
            return (void)(std::cout << "Error: out of range\n");

        values.push_back(static_cast<int>(n));
    }

    if (values.empty())
        return (void)(std::cout << "Error: no numbers\n");

    // work with values here
}