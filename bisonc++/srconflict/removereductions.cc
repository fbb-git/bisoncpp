#include "srconflict.ih"

void SRConflict::removeReductions(StateItem::Vector &itemVector)
{
    for_each
    (
        d_rmReduction.begin(), d_rmReduction.end(),
        Wrap1c<RmReduction, StateItem::Vector>(
                                    StateItem::removeReduction, itemVector)
    );
}
