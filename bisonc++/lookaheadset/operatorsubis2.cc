#include "lookaheadset.ih"

LookaheadSet &LookaheadSet::operator-=(Symbol const *symbol)
{
    if (symbol == Rules::eofTerminal())
        d_EOF = e_withoutEOF;
    else
        reinterpret_cast<ElementSet *>(this)->erase(symbol);

    return *this;
}
