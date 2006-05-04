#include "state.ih"

    // Pass a LA to a destination state
    // Do nothing if there is no destination state
    // Combine all LA's of all production the next kernel's production rules
    // (add all LAs of the lhs-symbols of the production rules)
    // then inspect the next state with that LA 
    // 
void State::propagateLookaheads(TransitionMapValue &transit,
                                TransitionMap &transitionMap)
{
    if (!transit.second->hasDestination())   // no destination state
        return;

        // 2nd element is empty-initialized LA set
    LookaheadContext laContext = {transitionMap};

    for_each(transit.second->kernelBegin(), transit.second->kernelEnd(), 
            Wrap1c<Item, LookaheadContext>(addLookaheads, laContext));

    msg() << indentinc << "Propagating LA " << laContext.la  << 
                        " to state " << transit.second->next() << info;

    s_state[transit.second->next()]->defineLookaheads(laContext.la);
}






