#include "reductions.ih"

void Reductions::setDefault()
{
    if (!d_count)                            // this state has no reductions
    {
        msg() << "   No reductions." << info;
        return;
    }

    if 
    (
        d_nTokens != Terminal::nActive()// this state doesn't use all
        &&                              // tokens for reductions, and it
        hasDefaultReduction()           // already has a default reduction
    )
    {
        msg() << "   Keeping _default_: " << d_nTokens << 
                 " non-default reductions specified" << info;
        return;
    }
                            // If this state also has a default transition, it
                            // is never reached since all tokens are used, so
                            // it can be removed.
    if (hasDefaultReduction())
    {
        if (!d_transitions[d_defaultReduction].size())
            d_transitions.erase(d_transitions.begin() + d_defaultReduction);
        else
            d_transitions[d_defaultReduction].setDefault(false);
    }
    
                            // now determine a new default.
    //  struct MaxTransition
    //  {
    //      unsigned max;
    //      Transition *maxTrans;
    //  };
    MaxTransition max = {0, 0};
    for_each(d_transitions.begin(), d_transitions.end(), 
            Wrap1c<Transition, MaxTransition>(&maxTransition, max));

    d_defaultReduction = max.maxTrans - &d_transitions.front();
    max.maxTrans->setDefault(true);

    msg() << "   Redefining the default reduction: now by rule " <<
              defaultReduction() << info;
}




