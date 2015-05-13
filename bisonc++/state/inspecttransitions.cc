#include "state.ih"


void State::inspectTransitions(set<size_t> &todo)
{
    for (StateItem const &item: d_itemVector)   // inspect all items
    {
                                        // obtain item's LA set
        LookaheadSet const &laSet = item.lookaheadSet();

        size_t next = item.next();      // offset in d_nextVector defining 
                                        // the state to transit to

        if (next == string::npos)       // no transition from this stateItem:
            continue;                   // continue with the next stateItem

        next = d_nextVector[next].next();  // idx of the state to transit to

        if (next == d_idx)          // ignore transitions to the current state
            continue;               // as that state's LA sets have already
                                    // been determined.

        State &dest = *s_state[next];   // info of the state to transit to
        
                                    // see if the dest state kernel item's LA
                                    // sets can be enlarged

        auto &kernel = d_nextVector[next].kernel();  // vector of item 
                                    // indices in the current state transiting
                                    // to kernel items in 'dest'

// WIP:

//    for (auto const &next: d_nextVector)
//    {
//        cout << next << '\n';
//        copy(next.kernel().begin(), next.kernel().end(), 
//             ostream_iterator<size_t>(cout, " "));
//        cout << "\n\n";        
//    }




        bool enlarged = false;
        for_each(dest.d_itemVector.begin(), 
                 dest.d_itemVector.begin() + dest.d_nKernelItems,
                [&](StateItem &stItem)
                {
                    if 
                    (
                        item.item().transitsTo(stItem.item())
                        && stItem.enlargeLA(laSet)
                    )
                        enlarged = true;
                }
            );

        if (enlarged)               // if LA sets of the destination state's
            todo.insert(next);      // kernel items were enlarged then
                                    // recompute its LA sets
    }       
}


