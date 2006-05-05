#include "state.ih"

void State::installLA(ReduceMapValue &reduction, 
                      TransitionMap &transmap)
{
    if (reduction.first != s_startProduction)
        reduction.second = 
                transmap[reduction.first->lhs()]->lookaheadSet();
}

