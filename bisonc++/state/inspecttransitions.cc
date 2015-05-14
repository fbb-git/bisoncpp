#include "state.ih"


void State::inspectTransitions(set<size_t> &todo)
{
    for (StateItem const &item: d_itemVector)   // inspect all items
    {
        size_t nextIdx = item.next();   // index in d_nextVector 
                                        // to use with StateItem `item'
                                // defining 
                                // the state to transit to

        if (nextIdx == string::npos)    // no transition from this StateItem:
            continue;                   // continue with the next StateItem

        Next const &next = d_nextVector[nextIdx];

        size_t nextState = next.next(); // the index of the state to transit 
                                        // to

        if (nextState == d_idx)     // ignore transitions to the current state
            continue;               // as that state's LA sets have already
                                    // been determined.

        State &dest = *s_state[nextState];  // info of the state to transit to
        
                                    // see if the dest state kernel item's LA
                                    // sets can be enlarged

        auto &kernel = next.kernel();  // item indices in the 
                                    // current state transiting to kernel 
                                    // items in 'dest'

// The Next elements in d_nextvector 
//    for (auto const &next: d_nextVector)
//    {
//        cout << next << '\n';
//        copy(kernel.begin(), kernel.end(), 
//             ostream_iterator<size_t>(cout, " "));
//        cout << "\n\n";        
//    }

                                        // obtain current item's LA set
        LookaheadSet const &laSet = item.lookaheadSet();

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
            todo.insert(nextState); // kernel items were enlarged then
                                    // recompute its LA sets
    }       
}




