#include "rules.hh"

void Rules::assignNonTerminalNumbers() 
{
    NonTerminal::setFirstNr(Terminal::maxValue() + 1);

    for_each(d_nonTerminal.begin(), d_nonTerminal.end(), 
                    &NonTerminal::setNr);
}
