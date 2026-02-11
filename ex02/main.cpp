#include "PmergeMe.hpp"


int main(int ac, char **av)
{
    if (ac != 2)
        return (std::cout << "Enter the unsorted array after the program name" << std::endl, 1);

    PmergeMe pm;
    if (!pm.processLine(av[1]))
        return 1;
    pm.execute();
    return 0;
}