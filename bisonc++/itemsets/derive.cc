#include "itemsets.ih"

// This function is part of the set of functions which determine whether a
// grammar derives any sentences. See derivesentence.cc

// Called by derivesentence.cc

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
        Wrap1c<State::ActionTable::value_type, ItemSets>
            (&ItemSets::deriveAction, *this));

    if (Production const *production = stateRef.defaultReduction())
        deriveInspectReduction(production);

    while (stateInfo.d_marked.size())
        deriveGoTo(stateInfo, state);               // perform shifts from
                                                    // the state's GoTo table
    d_stack.pop_back();

    // cerr << "leaving derive(" << state << ")\n";
}




