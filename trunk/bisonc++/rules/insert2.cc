#include "rules.ih"

NonTerminal *Rules::insert(NonTerminal *nonTerminal)
{
    d_nonTerminal.push_back(nonTerminal);

    return d_nonTerminal.back();
}
