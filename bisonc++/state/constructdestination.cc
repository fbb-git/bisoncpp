#include "state.ih"

void State::constructDestination(TransitionMapValue &transit)
{
    size_t/*unsigned*/ next = transit.second->next();
    if (next != UINT_MAX)       // no transitions
        s_state[next]->construct();
}






