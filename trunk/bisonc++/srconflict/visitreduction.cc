#include "srconflict.ih"

// Assume the itemVector of a state is as follows (StateItems):
//     0:    [P11 3] expression -> expression '-' expression  .   
//                     { EOLN '+' '-' '*' '/' ')' }  0, 1, () -1 
//     1:    [P10 1] expression -> expression  . '+' expression   
//                     { EOLN '+' '-' '*' '/' ')' }  0, 0, () 0 
//     2:    [P11 1] expression -> expression  . '-' expression   
//                     { EOLN '+' '-' '*' '/' ')' }  0, 0, () 1 
//     3:    [P12 1] expression -> expression  . '*' expression   
//                     { EOLN '+' '-' '*' '/' ')' }  0, 0, () 2 
//     4:    [P13 1] expression -> expression  . '/' expression   
//                     { EOLN '+' '-' '*' '/' ')' }  0, 0, () 3 
// 
// and the associated nextVector is:
// 
//     0:    On '+' to state 15 with (1 )
//     1:    On '-' to state 16 with (2 )
//     2:    On '*' to state 17 with (3 )
//     3:    On '/' to state 18 with (4 )
// 
// 
// Conflicts are inspected for all reduction elements, so for index element 0
// in the above example, as follows:
// 
//     1. The nextVector's symbols are search in the LA set of the reduction
//        item (so, subsequently '+', '-', '*' and '/' are searched in the LA
//        set of itemVector[0].
//     2. In this case, all are found and depending on the token's priority
//        and the rule's priority either a shift or a reduce is selected. 
//  
//  Production rules received their priority setting either explicitly (using
//  %prec) or from their first terminal token. See also 
//  rules/updateprecedences.cc

void SRConflict::visitReduction(size_t idx, SRConflict &context)
{
    Next::ConstIter nextIter = context.d_nextVector.begin();

    while (true)
    {
        nextIter =                  // check whether the a nextVector symbol
            find_if(                // is in the reduction item's LA set.
                nextIter, context.d_nextVector.end(), 
                FnWrap1c<Next const &, LookaheadSet const &, bool>(
                    Next::inLAset, context.d_itemVector[idx].lookaheadSet())
            );

        if (nextIter == context.d_nextVector.end())
            return;

        context.processShiftReduceConflict(nextIter, idx);
        ++nextIter;
    }
}
