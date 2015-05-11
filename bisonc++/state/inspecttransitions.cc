#include "state.ih"

void State::inspectTransitions(set<size_t> &todo)
{
    for (StateItem const &item: d_itemVector)   // inspect all items
    {
        LookaheadSet const &laSet = item.lookaheadSet();

        size_t next = item.next();      // offset in d_nextVector defining 
                                        // the state to transit to

        if (next == string::npos)   // no transition: ignore this stateItem
            continue;

        next = d_nextVector[next].next();  // idx of the state to transit to

        if (next == d_idx)          // ignore transitions to the current state
            continue;

        State &dest = *s_state[next];   // info of the state to transit to
        
                                    // see if the dest state kernel item's LA
                                    // sets can be enlarged
        bool enlarged = false;
        for_each(dest.d_itemVector.begin(), 
                 dest.d_itemVector.begin() + dest.d_nKernelItems,
                [&](StateItem &stItem)
                {
                    if (stItem.enlargeLA(laSet))
                        enlarged = true;
                }
            );

        if (enlarged)               // if LA sets of the destination state's
            todo.insert(next);      // kernel items were enlarged then
                                    // recompute its LA sets
    }       
}


