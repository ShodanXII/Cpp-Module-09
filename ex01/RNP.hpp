#pragma once 


#include <iostream>
#include <string>
#include <stack>

class RNP
{
private:
    std::stack<double> _stack;
public:
    RNP();
    RNP( const RNP &other );
    ~RNP( void );
    RNP &operator=( const RNP &other );

    void processLine( const std::string &line );
};
