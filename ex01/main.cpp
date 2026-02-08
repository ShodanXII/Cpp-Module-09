#include "RNP.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Usage: " << av[0] << " RNP sequence " << std::endl;
        return 1;
    }
    RNP rnp;
    rnp.processLine(av[1]);
    return 0;
}