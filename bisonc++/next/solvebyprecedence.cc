#include "next.ih"

Next::Solution Next::solveByPrecedence(Symbol const *productionSymbol) const
{
    switch (Terminal::comparePrecedence(d_symbol, productionSymbol))
    {
        default:    // EQUAL:
        return UNDECIDED;

        case Terminal::SMALLER:             // shift precedence < prod. prec.
        return REDUCE;

        case Terminal::LARGER:              // shift precedence > prod. prec.
        return SHIFT;
    }
}
