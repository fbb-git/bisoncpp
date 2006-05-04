#include "stateinfo.ih"

StateInfo::StateInfo(State const *state) 
:
    d_state(state),
    d_reducible(d_state->defaultReduction()),
    d_begin(state->transitionMap().begin()),
    d_end(state->transitionMap().end())
{}
