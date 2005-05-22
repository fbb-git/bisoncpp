#include "nonterminal.ih"

void NonTerminal::showFollow(NonTerminal const *nonTerminal)
{
    showName(nonTerminal->name());
    msg() << nonTerminal->d_follow << info;
}
