#include "parser.ih"

bool Parser::dollarIdx(int idx, size_t nElements) const
{
    if (idx <= static_cast<int>(nElements))
        return true;

    emsg << d_rules.name() << ": refers to element " << idx << 
        ". This rule has " << nElements << " elements" << 
        endl;
    return false;
}
