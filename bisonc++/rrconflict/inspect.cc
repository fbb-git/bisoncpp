#include "rrconflict.hh"

void RRConflict::inspect()
{
    for (unsigned first = 0; first < d_reducible.size(); ++first)
        visitReduction(first);
}
