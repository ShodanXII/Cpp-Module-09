#include "PmergeMe.hpp"


int main(int ac, char **av)
{
    if (ac < 2)
        return (std::cout << "Error" << std::endl, 1);

    PmergeMe pm;
    
    // Build a single string from all arguments
    std::string input;
    for (int i = 1; i < ac; ++i)
    {
        if (i > 1)
            input += " ";
        input += av[i];
    }
    
    if (!pm.processLine(const_cast<char*>(input.c_str())))
        return 1;
    pm.execute();
    return 0;
}