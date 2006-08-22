#include "state.ih"

void State::detectSR(ReduceMap::value_type &reduction, SRContext2 &src)
{
    // RR conflicts have already been solved, so any T symbol is used at
    // most once in a reduction. Consequently, a single find can be used
    // to detect a S/R conflict for a given T-symbol. 
    // 
    // Before 1.4.0: A S/R conflict occurs if the rule's continuation T
    // also appears in the LA set of a reducible rule.
    //

    src.reduction = &reduction;
    for_each(src.state.d_kernel.begin(), src.state.d_kernel.end(),
        Wrap1c<Item, SRContext2>(checkSRConflict, src));
}
