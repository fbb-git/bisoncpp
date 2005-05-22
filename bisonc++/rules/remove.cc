#include "rules.ih"

void Rules::remove(NonTerminal *np) 
{
    d_nonTerminal.erase(find(d_nonTerminal.begin(), d_nonTerminal.end(), np));
    delete np;
}
