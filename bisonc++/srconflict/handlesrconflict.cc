#include "srconflict.ih"

void SRConflict::handleSRconflict(
        size_t shiftableItemIdx,
        Next::ConstIter const &next, 
        size_t reducibleItemIdx)
{
    typedef Enum::Solution Solution;

    StateItem::Vector const &itemVector = d_itemVector;
    Symbol const *productionSymbol = 
                                itemVector[reducibleItemIdx].precedence();
    bool forced = false;

    Solution solution;

    if (productionSymbol == 0)              // no production rule precedence
    {
        solution = Solution::REDUCE;        // force a reduction
        forced = true;
        ++s_nConflicts;                     // and a conflict
    }
    else                                    // otherwise try to solve by 
    {                                       // precedence or association
        solution = next->solveByPrecedence(productionSymbol);

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

