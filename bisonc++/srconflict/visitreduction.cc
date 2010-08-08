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
//  One approach is that in this case no priority is available and so a
//  conflict is observed.
//
// ===========================================================================
// 
// On the other hand (as pointed out by Ramanand Mandayam), S/R conflicts may
// also have shifts in a production rule of N-terminal 'a' and reductions to a
// N-terminal 'b'. Here is an example: 
// 
// %left  '*'                                
// %token ID
// %%
// expr: 
//     term 
// ;
// 
// term:
//     term '*' primary
// | 
//     ID
// ;
// 
// primary:
//     '-' expr
// | 
//     ID
// ;
// 
// This grammar contains the following state
// 
// State 2:
// 0: [P1 1] expr -> term  .   { <EOF> }  1, () -1
// 1: [P2 1] term -> term  . '*' primary   { '*' <EOF> }  0, () 0
//   0: On '*' to state 4 with (1 )
//   Reduce item(s): 0 
// 
// Here, the reduction reduces to N 'expr' and the shift happens in a
// production rule of the N 'term'.
// 
// In these cases the S/R conflict should not be solved by priority or
// association as the reduction does not pertain to the production rules of
// the N in which the shift.

    // idx is the index of a reducible item. That item can be reached as
    // context.d_itemVector[idx]
void SRConflict::visitReduction(size_t reducibleIdx, SRConflict &context)
{
    auto nextIter = context.d_nextVector.begin();
    auto reducibleLAset = context.d_itemVector[reducibleIdx].lookaheadSet();

    while (true)
    {
        nextIter =                  // check whether a nextVector symbol
            find_if(                // is in the reduction item's LA set.
                nextIter, context.d_nextVector.end(), 
                FnWrap::unary(Next::inLAset, reducibleLAset)
            );

        if (nextIter == context.d_nextVector.end())
            return;
        
        context.processShiftReduceConflict(nextIter, reducibleIdx);
        ++nextIter;
    }
}








