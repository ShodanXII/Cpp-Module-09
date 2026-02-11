#include "PmergeMe.hpp"


int main(int ac, char **av)
{
    if (ac < 2)
    {
        std::cout << "Error" << std::endl;
        return 1;
    }
    PmergeMe pm;
    for (int i = 1; i < ac; ++i)
        pm.addNumber(av[i]);
    pm.execute();
    return 0;
}