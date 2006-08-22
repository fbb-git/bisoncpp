#include "state.ih"

	// In order to find S/R conflict, consider the following truth table:
	// 
	// (r.rhs: reducible rule rhs, k.rhs: kernel item rhs, k.dotSymOr0: symbol
    // at dot for kernel item or 0 (at end), r.LA: reducible rule's LA set)
	// 
	// r.rhs == k.rhs  r.LA >= k.dotSymOr0         S/R
	// -----------------------------------------------
	//        1              1                     1
	//        1              0                     0
	//        0              1                     0
	//        0              0                     0
	// -----------------------------------------------
	// 
	// So, all reducible rules are visited. For each reducible rule the S/R
	// condition is checked in the kernel items, and if found, solved as
    // follows: 
    
    //  REDUCE is preferred over SHIFT if:
    //      - the pri. of the reduction exceeds the priority of the shift;
    //      - the priorities are equal, but the association is left.
    //
    // In the opposite situation, SHIFT is preferred (pri(R) < pri(S), or
    // R-association).
    //
    // If no choice is found from the info in the configuration file, SHIFT is
    // used, and a true S/R conflict is reported. 
    //
    // With SHIFT, the terminal T is removed from the reduction's LA set
    // With REDUCE, the terminal's entry from the transitionMap is removed.
    // 
    // If, following the above decisions, a state has only one reduce action,
    // then the reduction becomes the default reduction.

void State::solveShiftReduceConflicts()
{
    SRContext2 src = {false, *this};

    msg() << "\nS/R Conflict test: reduction size: " << d_reduce.size() << 
                                                                        info;
    
    Indent::inc();
    for_each(d_reduce.begin(), d_reduce.end(), 
        Wrap1c<ReduceMap::value_type, SRContext2>(detectSR, src));
    Indent::dec();

//  ORG CODE:
//    if (!d_reduce.size() || !d_nTransitions)
//        return;                 // no SR conflicts here
//
//    Indent::inc();
//    for_each(d_transition.begin(), d_transition.end(),
//            Wrap1c<TransitionMapValue, SRContext>(detectSR, src));
//    Indent::dec();
}
