#include "rrconflict.ih"

void RRConflict::removeConflicts(StateItem::Vector &itemVector)
{
    for_each
    (
        d_rmReduction.begin(), d_rmReduction.end(),
        FnWrap::unary(StateItem::removeRRConflict, itemVector)
    );
}
