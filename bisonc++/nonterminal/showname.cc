#include "nonterminal.ih"

void NonTerminal::showName(string const &name)
{
    msg() << "   " << name << left <<
            setw(max(10 - static_cast<int>(name.length()), 1)) << ":" << 
            " " << spool;
}
