#include "stateinfo.ih"

bool StateInfo::acceptTerminal(State::TransitionMapValue const &transit,
                               State const &state)
{
    return 
        transit.first->isTerminal() 
        && 
        transit.second->hasDestination();
}

