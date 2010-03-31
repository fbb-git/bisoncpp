#include "state.ih"

vector<State *> State::s_state;

State *State::s_acceptState;

ostream &(State::*State::s_insert)(ostream &out) const;
