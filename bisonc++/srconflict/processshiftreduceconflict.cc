#include "srconflict.ih"

    // called by visitreduction.cc
    //
    //  Next::ConstIter const &next: 
    //     the element in an item's next-set that has a LA symbol that is also
    //      found in the LA set of a reducible item
    //
    //  size_t reducibleItemIdx: the index of the reducible item.
    
void SRConflict::processShiftReduceConflict(Next::ConstIter const &next, 
                                            size_t reducibleItemIdx)
{
    for (auto shiftableItemIdx: next->kernel())
        handleSRconflict(shiftableItemIdx, next, reducibleItemIdx);
}
