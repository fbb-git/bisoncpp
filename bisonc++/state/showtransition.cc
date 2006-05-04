#include "state.ih"

void State::showTransition(TransitionMapValue const &transit) 
{
    if (transit.second->hasDestination())
        msg() << indent << 
            "On " << transit.first->display() << " shift and push state " <<
                     transit.second->next() << info;
}
