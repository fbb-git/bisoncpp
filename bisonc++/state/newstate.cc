#include "state.hh"

State &State::newState()
{
    State *ret = new State(s_state.size());
    s_state.push_back(ret);
    return *ret;
}
