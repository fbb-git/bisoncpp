#include "state.ih"

void State::solveReduceReduceConflicts()
{
    for_each(d_reduce.begin(), d_reduce.end(),
            Wrap1c<ReduceMapValue, TransitionMap> (installLA, d_transition));

    RRContext rrc = {false, d_idx};

    if (d_reduce.size() <= 1)
        return;
    
    Indent::inc();
    
    for 
    (
        ReduceMapIterator begin = d_reduce.begin(),
                            end = d_reduce.end();
            begin != end;
                // increment in the compound
    )
    {
        if (begin->second.empty())
        {
            ++begin;
            continue;
        }

        rrc.reduceIter = begin;
        rrc.leftReductionDisplayed = false;

        Indent::inc();
        for_each(++begin, end, 
            Wrap1c<ReduceMapValue, RRContext>
                 (compareReductions, rrc));
        Indent::dec();
    }
    Indent::dec();
}
