#include "rrconflict.ih"

void RRConflict::visitReduction(size_t first)
{
    d_firstIdx = d_reducible[first];
    d_firstLA = &d_itemVector[d_firstIdx].lookaheadSet();

                            // this MUST be second < d_reducible.size() !!
    for (size_t second = first + 1; second < d_reducible.size(); ++second)
        compareReductions(second);
}
