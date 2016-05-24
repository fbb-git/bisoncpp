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
// Conflicts are inspected for all reducible elements, so for index element 0
// in the above example, as follows:
// 
//     1. The nextVector's symbols are searched in the LA set of the reduction
//        item (so, subsequently '+', '-', '*' and '/' are searched in the LA
//        set of itemVector[0].
//     2. In this case, all are found and depending on the token's priority
//        and the rule's priority either a shift or a reduce is selected. 
//  
//  Production rules received their priority setting either explicitly (using
//  %prec) or from their first terminal token. See also 
//  rules/updateprecedences.cc
//
//  What happens if neither occurs? In a rule like 'expr: term' there is no
//  first terminal token and there is no %prec being used. 
//  In these cases the rule automatically receives the highest precedence and 
//  a shift/reduce conflict is reported (as pointed out by Ramanand
//  Mandayam).

    // idx is the index of a reducible item. That item can be reached as
    // d_itemVector[idx]
void SRConflict::visitReduction(size_t reducibleIdx)
{
    auto nextIter = d_nextVector.begin();
    auto reducibleLAset = d_itemVector[reducibleIdx].lookaheadSet();

    while (true)
    {
        nextIter =                  // check whether a nextVector symbol
            find_if(                // is in the reduction item's LA set.
                nextIter, d_nextVector.end(),   // if so, there is a S/R
                [&](Next const &next)           // conflict, solved below
                {
                    return next.inLAset(reducibleLAset);
                }
            );

        if (nextIter == d_nextVector.end())
            return;

        processShiftReduceConflict(nextIter, reducibleIdx);
        ++nextIter;
    }
}







