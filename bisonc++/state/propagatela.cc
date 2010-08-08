#include "state.ih"

// LA propagation proceeds as follows: In a cycle visit all state items. When 
// a state item X has its LA_enlarged flag set, 
//      Set its nextEnlarged flag
//      Lower its LA_enlarged flag
//      Visit its dependent items, and determine their LA set from the item at
// its dot-position and X's LA set. If this results in an enlarged LA set of
// the dependent item, raise its LA_enlarged flag.
// Iterate until no more LA_enlarged flags are set

void State::propagateLA()
{
    while 
    (
        find_if(
            d_itemVector.begin(), d_itemVector.end(), 
            FnWrap::unary(StateItem::propagateLA, d_itemVector)
        ) != d_itemVector.end()
    )
        ;

    // at this point the LA sets of the current state have been determined.
    // next, inspect the child states for updates.
 
    LookaheadContext context = 
    {
        vector<State *>(), // child states to visit, 
        d_itemVector,
                           // remaining fields managed by distributeLA
    };

    for_each(d_nextVector.begin(), d_nextVector.end(),
        FnWrap::unary(distributeLA, context));

    for_each(context.child.begin(), context.child.end(), staticPropagateLA);
}



