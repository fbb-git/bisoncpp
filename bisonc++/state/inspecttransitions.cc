#include "state.ih"


void State::inspectTransitions(set<size_t> &todo)
{
cout << "\nState " << d_idx << ": transitions to other states\n";

for (Next const &next: d_nextVector)
{
    size_t nextStateIdx = next.next();

    if (nextStateIdx == string::npos)
        continue;

    for (size_t nextIdx = 0; nextIdx != next.kernel().size(); ++nextIdx)
    {
        size_t thisIdx = next.kernel()[nextIdx];

        StateItem const &thisItem = d_itemVector[thisIdx];

        State &nextState = *s_state[nextStateIdx];

        StateItem &nextItem = nextState.d_itemVector[nextIdx];

        cout << "\n       From Item " << thisIdx << 
                " (" << thisItem << ")\n"
                " to state " << next.next() << " item " << nextIdx <<
                " (" << nextItem << ")\n";

//        if (not thisItem.item().transitsTo(nextItem.item()))
//            cout << "NO TRANSITION!!\n\n";

        if (nextItem.enlargeLA(thisItem.lookaheadSet()))
        {
            cout << "   new LA set: " << nextItem.lookaheadSet() << 
                    "   recompute " << nextStateIdx << '\n';
            
            todo.insert(nextStateIdx); // kernel items were enlarged then
                                    // recompute its LA sets
        }
    }
}

return;


cout << '\n';

size_t srcItemIdx = 0;

    for (StateItem const &item: d_itemVector)   // inspect all items
    {
//cout << "\n";
    //       inspecting item " << srcItemIdx << ": " << item.item() << "\n";

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

                                        // obtain current item's LA set
        LookaheadSet const &laSet = item.lookaheadSet();

size_t destItemIdx = 0;

        for_each(dest.d_itemVector.begin(), 
                 dest.d_itemVector.begin() + dest.d_nKernelItems,
                [&](StateItem &stItem)
                {
                    if 
                    (
                        item.item().transitsTo(stItem.item())
                        && stItem.enlargeLA(laSet)
                    )
{
cout << "   from " << srcItemIdx << " to state " << nextState << " item " <<
            destItemIdx << '\n';

            todo.insert(nextState); // kernel items were enlarged then
                                    // recompute its LA sets
}
                ++destItemIdx;
                }
            );

    ++srcItemIdx;
    }
}




