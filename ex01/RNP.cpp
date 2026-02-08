#include "RNP.hpp"

#include <cctype>

RNP::RNP() {}

RNP::RNP(const RNP &other) : _stack(other._stack) {}

RNP &RNP::operator=(const RNP &other)
{
    if (this != &other)
        _stack = other._stack;
    return *this;
}

RNP::~RNP() {}

void RNP::processLine(const std::string &line)
{
    for (int i = 0; i < static_cast<int>(line.size()); i++)
    {
        char ch = line[i];

        if (ch == ' ')
            continue;
        else if (std::isdigit(static_cast<unsigned char>(ch)))
            _stack.push(static_cast<double>(ch - '0'));
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        {
            if (_stack.size() < 2)
            {
                std::cerr << "Error" << std::endl;
                return;
            }

            double rhs = _stack.top();
            _stack.pop();
            double lhs = _stack.top();
            _stack.pop();

            if (ch == '+')
                _stack.push(lhs + rhs);
            else if (ch == '-')
                _stack.push(lhs - rhs);
            else if (ch == '*')
                _stack.push(lhs * rhs);
            else if (ch == '/')
            {
                if (rhs == 0)
                {
                    std::cerr << "Error" << std::endl;
                    return;
                }
                _stack.push(lhs / rhs);
            }
        }
        else
        {
            std::cerr << "Error" << std::endl;
            return;
        }
    }

    if (_stack.size() != 1)
    {
        std::cerr << "Error" << std::endl;
        return;
    }

    std::cout << _stack.top() << std::endl;
}