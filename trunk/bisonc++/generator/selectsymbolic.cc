#include "generator.ih"

void Generator::selectSymbolic(Terminal const *terminal,
                               Terminal::ConstVector *symbolicTokens)
{
    if 
    (
        terminal->isSymbolic()
        && 
        terminal->value() > Rules::eofTerminal()->value()
    )
        symbolicTokens->push_back(terminal);
}
