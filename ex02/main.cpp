#include "PmergeMe.hpp"


int main(int ac, char **av)
{
    if(ac != 2) return (std::cout << "Enter the unsorted array after the program name" << std::endl, 1);
    PmergeMe pm;
    pm.processLine(av[1]);
    return 0;
}