#include "srconflict.ih"

void SRConflict::handleSRconflict(
        size_t shiftableItemIdx,
        SRConflict &context,
        Next::ConstIter const &next, 
        size_t reducibleItemIdx)
{
    typedef Enum::Solution Solution;

    StateItem::Vector const &itemVector = context.d_itemVector;

    Solution solution;

    if 
    (
        itemVector[reducibleItemIdx].item().lhs()
        != itemVector[shiftableItemIdx].item().lhs()
    )
        solution = Solution::UNDECIDED;
    else
    {
        solution = next->solveByPrecedence(
                            itemVector[reducibleItemIdx].precedence()
                         );

        if (solution == Solution::UNDECIDED)
            solution = next->solveByAssociation();
    }
    
    bool forced = false;

    switch (solution)
    {
        case Solution::REDUCE:
            context.d_rmShift.push_back(next - context.d_nextVector.begin());
        return;

        case Solution::UNDECIDED:
            forced = true;
            ++s_nConflicts;
        break;
        
        default:    // case SHIFT:
        break;
    }
    
    context.d_rmReduction.push_back(
                                RmReduction(reducibleItemIdx, next->next(), 
                                            next->symbol(), forced
                                )
                          );
}
