#include "state.ih"

void State::solveShiftReduceConflicts()
{
    SRContext src = {false, *this};

    if (!d_reduce.size() || !d_nTransitions)
        return;                 // no SR conflicts here

    Indent::inc();
    for_each(d_transition.begin(), d_transition.end(),
            Wrap1c<TransitionMapValue, SRContext>(detectSR, src));
    Indent::dec();
}
