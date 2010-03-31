#include "terminal.ih"

#include <iostream>

// reserved terminals are defined by default in the share/bisonc++ skeleton,
// and therefore do not need assigned values.

Terminal::Terminal(string const &name, string const &literal, Type type)
:
    Symbol(name, type, ""),
    d_value(0),
    d_association(UNDEFINED),
    d_precedence(s_precedence),
    d_literal(literal),
    d_readableLiteral(literal),
    d_firstSet(this)
{
    setReserved();
}



