#include "generator.ih"

void Generator::selectSymbolic(Terminal const *terminal, SSContext &context)
{
    if 
    (
        terminal->isSymbolic()
        && 
        terminal->value() > Rules::eofTerminal()->value()
    )
        context.symbolicTokens->push_back(terminal);
}
