#include "production.ih"

Production::Production(Symbol const *nonTerminal)
:
    d_precedence(0),
    d_nonTerminal(nonTerminal),
    d_nr(++s_nr)
{}
