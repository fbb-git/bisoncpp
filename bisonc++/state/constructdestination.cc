#include "state.ih"

void State::constructDestination(TransitionMapValue &transit)
{
    unsigned next = transit.second->next();
    if (next != UINT_MAX)       // no transitions
        s_state[next]->construct();
}






