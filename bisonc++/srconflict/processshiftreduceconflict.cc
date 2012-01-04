#include "srconflict.ih"

void SRConflict::processShiftReduceConflict(Next::ConstIter const &next, 
                                            size_t reducibleItemIdx)
{
    for (auto shiftableItemIdx: next->kernel())
        handleSRconflict(shiftableItemIdx, next, reducibleItemIdx);
}
