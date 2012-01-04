#include "srconflict.ih"

void SRConflict::removeReductions(StateItem::Vector &itemVector)
{
    for (auto &rm: d_rmReduction)
        StateItem::removeReduction(rm, itemVector);
}
