#include "lookaheadset.ih"

LookaheadSet &LookaheadSet::operator-=(Symbol const *symbol)
{
    if (symbol == Rules::eofTerminal())
        d_EOF = false;
    else
        reinterpret_cast<Baseclass *>(this)->erase(symbol);

    return *this;
}
