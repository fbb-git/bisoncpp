#include "state.ih"

Transition *State::transitionOf(Symbol const *symbol)
{
                                // Transition to use for transitions to a new
                                // state
    Transition *transition = new Transition;

                                // Enter or lookup the next state
    pair<TransitionMapIterator, bool> 
        nextState = d_transition.insert
                    (
                        TransitionMapValue(symbol, transition)
                    );

    // second: bool indicating whether a new transition was inserted (if true)
    if (!nextState.second)      // if false: existing transition
    {
        delete transition;      // delete unused allocated Transition
                                // point `transition' to the existing one
        transition = nextState.first->second;
    }

    return transition;
}
