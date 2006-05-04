#include "state.ih"

void State::tuneAcceptState() 
{
    d_reduce.erase(s_startProduction);

    for_each(d_transition.begin(), d_transition.end(), noShiftOnEOF);
}
