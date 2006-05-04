#include "rrconflict.ih"

RRConflict::RRConflict(LookaheadSet const &laSet, 
                       Production const *one, Production const *other)
:
    d_laSet(laSet)
{
    if (one->nr() > other->nr())
        swap(one, other);
    first = one;
    second = other;
}
