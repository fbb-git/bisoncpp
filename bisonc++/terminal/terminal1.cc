#include "terminal.ih"

#include <iostream>

Terminal::Terminal(string const &name, Type type, unsigned value, 
                   Association association, std::string const &stype)
:
    Symbol(name, type, stype),
    d_value(value == DEFAULT ? s_value++ : value),
    d_association(association),
    d_priority(s_priority),
    d_literal(name),
    d_firstSet(this)
{
    if (d_value > s_maxValue)
        s_maxValue = d_value;
}



