#include "generator.ih"

void Generator::selectSymbolic(Terminal const *terminal,
                               Terminal::ConstVector &symbolicTokens)
{
    if 
    (
        (
            terminal->isSymbolic()
            ||
            (terminal->isUsed() && terminal->isUndetermined())
        )
        && 
        terminal->size() > Rules::eofTerminal()->size()
    )
        symbolicTokens.push_back(terminal);
}
