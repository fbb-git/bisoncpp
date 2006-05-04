#include "stateinfo.ih"

Symbol const *StateInfo::nextToken()
{
    d_begin = find_if(d_begin, d_end, 
                    Wrap1c<State::TransitionMapValue, State, bool>
                          (acceptTerminal, *d_state));

    return d_begin == d_end ?
                0
            :
                d_begin++->first;
}
