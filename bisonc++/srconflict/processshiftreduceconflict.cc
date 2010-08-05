#include "srconflict.ih"

void SRConflict::processShiftReduceConflict(Next::ConstIter const &next, 
                                            size_t reducibleItemIdx)
{
    typedef Enum::Solution Solution;

    Solution solution;

    if 
    (
        differentLHSs(
            d_itemVector[reducibleItemIdx].item().lhs(), 
            next->kernel()
        )
    )
        solution = Solution::UNDECIDED;
    else
    {
        solution =
        next->solveByPrecedence(d_itemVector[reducibleItemIdx].precedence());

        if (solution == Solution::UNDECIDED)
            solution = next->solveByAssociation();
    }

//    cerr << "Reducible item = " << reducibleItemIdx << ", shifting item: " <<
//            next->kernel()[0] << endl;
//    cerr << "LHS reducible: " << 
//            d_itemVector[reducibleItemIdx].item().lhs() << endl;
//    cerr << "LHS shiftable: " << 
//            d_itemVector[next->kernel()[0]].item().lhs() << endl;
    
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
    
    d_rmReduction.push_back(RmReduction(reducibleItemIdx, next->next(), 
                                        next->symbol(), forced));
}
