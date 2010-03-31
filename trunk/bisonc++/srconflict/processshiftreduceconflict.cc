#include "srconflict.ih"

void SRConflict::processShiftReduceConflict(Next::ConstIter const &next, 
                                            size_t itemIdx)
{
    typedef Enum::Solution Solution;

    Solution solution =
            next->solveByPrecedence(d_itemVector[itemIdx].precedence());

    if (solution == Solution::UNDECIDED)
        solution = next->solveByAssociation();
    
    bool forced = false;
    switch (solution)
    {
        case Solution::REDUCE:
            d_rmShift.push_back(next - d_nextVector.begin());
        return;

        case Solution::UNDECIDED:
            forced = true;
            ++s_nConflicts;
        break;
        
        default:    // case SHIFT:
        break;
    }
    
    d_rmReduction.push_back(RmReduction(itemIdx, next->next(), 
                                        next->symbol(), forced));
}
