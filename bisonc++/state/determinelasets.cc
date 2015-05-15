#include "state.ih"

// The LA sets of the items of a state (state tt(idx)) are computed by first
// computing the LA sets of its items, followed by propagating the LA sets of
// items to the states for which state transitions have been defined. Then,
// the LA sets are computed for all items of all modified states: 

namespace
{
    size_t zero;
}

void State::determineLAsets() 
{
    set<size_t> todo(&zero, &zero + 1); // initialize to the first State idx.

    while (not todo.empty())
    {
        auto iter = todo.begin();

        State &state = *s_state[*iter]; // determine LA sets of the items of
                                        // this state.
        todo.erase(iter);

        state.computeLAsets();          // compute the LA sets of `state's 
                                        // items

        state.inspectTransitions(todo); // possibly update the LA sets of
                                        // kernel items of states to which a
                                        // transition is possible from
                                        // `state'. If so, the indices of
                                        // those target states are inserted
                                        // into `todo', causing the LA sets of
                                        // their items to be recomputed.
    }
}







