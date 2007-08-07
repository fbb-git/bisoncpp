#include "next.ih"

Next::Solution Next::solveByAssociation() const
{
    switch (Terminal::downcast(d_symbol)->association())
    {
        default:
        return UNDECIDED;

        case Terminal::NONASSOC:            // left or nonassoc: reduce first
        case Terminal::LEFT:
        return REDUCE;

        case Terminal::RIGHT:               // right assoc.: shift first
        return SHIFT;
    }
}
