#include "nonterminal.ih"

void NonTerminal::showFirst(NonTerminal const *nonTerminal)
{
    showName(nonTerminal->name());
    msg() << nonTerminal->d_first << info;
}
