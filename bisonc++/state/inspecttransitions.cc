#include "state.ih"

// All Next objects in the state's d_nextVector are inspected. The Next 
// objects hold 
//  - the state index of a state to transfer to from the current state
//  - a size_t vector of item transitions. Each element is the index of an
//    item in the current state (the source-item), its index is the index of a
//    (kernel) item of the state to transfer to (the destination index).
// If the LA set of the destination item is enlarged using the LA set of the
// source item then then the LA sets of the destination state's items must be
// recomputed. This is realized by inserting the destation state's index into
// the `todo' set.

void State::inspectTransitions(set<size_t> &todo)
{
    for (Next const &next: d_nextVector)
    {
        size_t nextStateIdx = next.next();
    
        if (nextStateIdx == string::npos)       // no transitions: try the
            continue;                           // next Next object

                                                // state to transfer to
        State &nextState = *s_state[nextStateIdx];
    
                                                // visit all source-destination
        for (                                   // item pairs
            size_t nextIdx = 0, end = next.kernel().size(); 
                nextIdx != end; 
                    ++nextIdx
        )                                   // if the dest. item's LA set is 
        {                                   // enlarged, recompute the LA sets 
            if (                            // of the dest. state's items.
                nextState.d_itemVector[nextIdx].enlargeLA(
                    d_itemVector[next.kernel()[nextIdx]].lookaheadSet()
                )
            )
                todo.insert(nextStateIdx); // kernel items were enlarged then
                                    // recompute its LA sets
        }
    }
}




