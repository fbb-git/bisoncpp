#include "rrconflict.ih"

void RRConflict::removeConflicts(StateItem::Vector &itemVector)
{
    for_each
    (
        d_rmReduction.begin(), d_rmReduction.end(),
        Wrap1c<RRData, StateItem::Vector>(
                                    StateItem::removeRRConflict, itemVector)
    );
}
