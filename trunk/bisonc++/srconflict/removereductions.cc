#include "srconflict.ih"

void SRConflict::removeReductions(StateItem::Vector &itemVector)
{
    for_each
    (
        d_rmReduction.begin(), d_rmReduction.end(),
        FnWrap::unary(StateItem::removeReduction, itemVector)
    );
}
