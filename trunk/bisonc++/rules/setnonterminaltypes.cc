#include "rules.ih"

void Rules::setNonTerminalTypes() 
{
    for_each(d_nonTerminal.begin(), d_nonTerminal.end(), 
             &NonTerminal::setNonTerminal);
}
