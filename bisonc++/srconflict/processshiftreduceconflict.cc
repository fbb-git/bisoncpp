#include "srconflict.ih"

void SRConflict::processShiftReduceConflict(Next::ConstIter const &next, 
                                            size_t itemIdx)
{
    Solution solution =
        next->solveByPrecedence(d_itemVector[itemIdx].precedence());

    if (solution == UNDECIDED)
        solution = next->solveByAssociation();
    
    bool forced = false;
    switch (solution)
    {
        case REDUCE:
            d_rmShift.push_back(next - d_nextVector.begin());
        return;

        case UNDECIDED:
            forced = true;
            ++s_nConflicts;
        break;
        
        default:    // case SHIFT:
        break;
    }        
    d_rmReduction.push_back(RmReduction(itemIdx, next->next(), 
                                        next->symbol(), forced));
}

