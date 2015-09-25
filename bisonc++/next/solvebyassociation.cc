#include "next.ih"

Next::Solution Next::solveByAssociation() const
{
    switch (Terminal::downcast(d_symbol)->association())
    {
        default:
        return Solution::UNDECIDED;

        case Terminal::NONASSOC:            // left or nonassoc: reduce first
        case Terminal::LEFT:
        return Solution::REDUCE;

        case Terminal::RIGHT:               // right assoc.: shift first
        return Solution::SHIFT;
    }
}
