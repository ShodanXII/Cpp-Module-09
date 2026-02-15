#pragma once 


#include <iostream>
#include <string>
#include <stack>

class RPN
{
private:
    std::stack<double> _stack;
public:
    RPN();
    RPN( const RPN &other );
    ~RPN( void );
    RPN &operator=( const RPN &other );

    void processLine( const std::string &line );
};
