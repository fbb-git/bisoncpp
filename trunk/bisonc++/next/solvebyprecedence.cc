#include "next.ih"

Next::Solution Next::solveByPrecedence(Symbol const *productionSymbol) const
{
    switch (Terminal::comparePrecedence(d_symbol, productionSymbol))
    {
        default:    // EQUAL:
        return Solution::UNDECIDED;

        case Terminal::SMALLER:             // shift precedence < prod. prec.
        return Solution::REDUCE;

        case Terminal::LARGER:              // shift precedence > prod. prec.
        return Solution::SHIFT;
    }
}
