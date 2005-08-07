#include "itemsets.ih"

// See derivesentence.cc

void ItemSets::derive(unsigned state) 
{
    // cerr << "calling derive(" << state << ")\n";

    d_stack.push_back(state);

    StateInfo &stateInfo    = d_stateInfo[state];   // set up some aliases
    State     &stateRef     = *d_state[state];      // to reduce address 
                                                    // computations below
    stateInfo.d_visited = true;

    State::ActionConstIterators actions = stateRef.actionConstIterators();

    for_each(actions.first, actions.second,
        Wrap1<State::ActionTable::value_type const &, ItemSets>
            (&ItemSets::deriveAction, *this));

    if (Production const *production = stateRef.defaultReduction())
        deriveInspectReduction(production);

    while (stateInfo.d_marked.size())
        deriveGoTo(stateInfo, state);               // perform shifts from
                                                    // the state's GoTo table
    d_stack.pop_back();

    // cerr << "leaving derive(" << state << ")\n";
}




