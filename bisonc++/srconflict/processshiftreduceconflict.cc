#include "srconflict.ih"

void SRConflict::processShiftReduceConflict(Next::ConstIter const &next, 
                                            size_t reducibleItemIdx)
{
    for_each(
        next->kernel().begin(), next->kernel().end(), 
        [&, reducibleItemIdx](size_t shiftableItemIdx)
        {
            handleSRconflict(shiftableItemIdx, next, reducibleItemIdx);
        }
    );
}
