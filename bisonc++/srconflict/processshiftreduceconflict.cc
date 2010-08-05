#include "srconflict.ih"

void SRConflict::processShiftReduceConflict(Next::ConstIter const &next, 
                                            size_t reducibleItemIdx)
{
    for_each(next->kernel().begin(), next->kernel().end(), 
        FnWrap::unary(
            handleSRconflict, 
            *this, 
            next, 
            reducibleItemIdx
        )
    );
}
//XX
//XX
//XX
//XX    Solution solution;
//XX
//XX    if 
//XX    (
//XX        differentLHSs(
//XX            d_itemVector[reducibleItemIdx].item().lhs(), 
//XX            next->kernel()
//XX        )
//XX    )
//XX        solution = Solution::UNDECIDED;
//XX    else
//XX    {
//XX        solution =
//XX        next->solveByPrecedence(d_itemVector[reducibleItemIdx].precedence());
//XX
//XX        if (solution == Solution::UNDECIDED)
//XX            solution = next->solveByAssociation();
//XX    }
//XX
//XX//    cerr << "Reducible item = " << reducibleItemIdx << ", shifting item: " <<
//XX//            next->kernel()[0] << endl;
//XX//    cerr << "LHS reducible: " << 
//XX//            d_itemVector[reducibleItemIdx].item().lhs() << endl;
//XX//    cerr << "LHS shiftable: " << 
//XX//            d_itemVector[next->kernel()[0]].item().lhs() << endl;
//XX    
//XX    bool forced = false;
//XX
//XX    switch (solution)
//XX    {
//XX        case Solution::REDUCE:
//XX            d_rmShift.push_back(next - d_nextVector.begin());
//XX        return;
//XX
//XX        case Solution::UNDECIDED:
//XX            forced = true;
//XX            ++s_nConflicts;
//XX        break;
//XX        
//XX        default:    // case SHIFT:
//XX        break;
//XX    }
//XX    
//XX    d_rmReduction.push_back(RmReduction(reducibleItemIdx, next->next(), 
//XX                                        next->symbol(), forced));
//XX                                        next->symbol(), forced));
//XX}
