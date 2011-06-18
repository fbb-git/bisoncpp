#include "srconflict.ih"

void SRConflict::removeReductions(StateItem::Vector &itemVector)
{
    for_each
    (
        d_rmReduction.begin(), d_rmReduction.end(),
        [&](RmReduction const &rm)
        {
            StateItem::removeReduction(rm, itemVector);
        }
    );
}
