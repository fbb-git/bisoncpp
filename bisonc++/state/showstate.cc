#include "state.ih"


void State::showState(State *state)
{
    msg() << indent << spool;
    state->show();
}

