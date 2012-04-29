#include "srconflict.ih"

    // called fm processshiftreduceconflict.cc

    // A conflict was observed as item 'reducibleItemIdx' and
    // 'shiftableItemIdx' have identical LA symbols
    //
void SRConflict::handleSRconflict(
        size_t shiftableItemIdx,
        Next::ConstIter const &next, 
        size_t reducibleItemIdx)
{
    typedef Enum::Solution Solution;

    StateItem::Vector const &itemVector = d_itemVector;
    Symbol const *precedence = itemVector[reducibleItemIdx].precedence();
    bool forced = false;

    Solution solution;
                                            // the reducible item does not
    if (precedence == 0)                    // have an explicit precedence
    {
        // solution = Solution::REDUCE;        // force a reduction
        solution = Solution::SHIFT;         // force a shift
        forced = true;
        ++s_nConflicts;                     // and a conflict
    }
    else                                    // otherwise try to solve by 
    {                                       // precedence or association
        solution = next->solveByPrecedence(precedence);

        if (solution == Solution::UNDECIDED)
            solution = next->solveByAssociation();
    }
    

    switch (solution)                       // perform SHIFT or REDUCE
    {
        case Solution::REDUCE:
            d_rmShift.push_back(
                                    RmShift(
                                        next - d_nextVector.begin(),
                                        forced)
                                );
        return;

        case Solution::UNDECIDED:
            forced = true;
            ++s_nConflicts;
        break;
        
        default:    // case SHIFT:
        break;
    }
    
    d_rmReduction.push_back(
                                RmReduction(reducibleItemIdx, next->next(), 
                                            next->symbol(), forced
                                )
                          );
}

