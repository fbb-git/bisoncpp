#include "state.ih"

    // Inspect the items of this transition. There may be none, then
    // done. Otherwise, find a state having all these items in its
    // kernel. This may be a new state. 
    // If the destination state is a new state, add the transition items to
    // that state's kernel. 

void State::defineDestination(TransitionMapValue &transit, 
                               State &state)
{
    if (transit.second->emptyKernel())      // no transitions
        return;

    ++state.d_nTransitions;

    unsigned idx;                           // find a destination state
    bool newState = findState(&idx, transit.second->kernel());

    Symbol const *symbol = transit.first;

    msg() << indent << "On `" << symbol->display() << "':" 
            " to state " << idx <<  info;

    if (symbol == Rules::errorTerminal())
        s_state[idx]->d_type = IS_ERROR_STATE;

    Transition &transition = *transit.second;
    transition.setNext(idx);
    
    if (!newState)
        return;

    Indent::inc();
    for_each(transition.kernelBegin(), transition.kernelEnd(), 
            Wrap1c<Item, State>(addKernelItem, *(s_state)[idx]));
    Indent::dec();
}






