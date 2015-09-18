#include "nonterminal.hh"

NonTerminal::NonTerminal(string const &name, string const &stype, Type type)
:
    Symbol(name, type, stype)
{}
