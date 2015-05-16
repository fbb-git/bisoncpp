#include "production.ih"

Production::Production(Symbol const *nonTerminal, size_t lineNr)
:
    d_precedence(0),
    d_nonTerminal(nonTerminal),
    d_nr(++s_nr),
    d_used(false),
    d_lineNr(lineNr),
    d_nameIdx(s_fileName.size() - 1)
{}
