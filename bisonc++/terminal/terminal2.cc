#include "terminal.ih"

#include <iostream>

Terminal::Terminal(string const &name, string const &literal, Type type)
:
    Symbol(name, type, ""),
    d_value(s_value++),
    d_association(UNDEFINED),
    d_priority(s_priority),
    d_literal(literal),
    d_readableLiteral(literal),
    d_firstSet(this)
{
    setReserved();
    if (d_value > s_maxValue)
        s_maxValue = d_value;
}



