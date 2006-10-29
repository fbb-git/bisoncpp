#include "state.ih"

State &State::newState(Type type)
{
    State *ret = new State(s_state.size(), type);
    s_state.push_back(ret);
    return *ret;
}
