#include "state.ih"

bool State::findState(size_t/*unsigned*/ *idx, vector<Item> const &kernel)
{
    StateVector::iterator sv_it = find_if(s_state.begin(), s_state.end(),
        Wrap1c<State, vector<Item>, bool>(searchStateWith, kernel));

    *idx = sv_it - s_state.begin();

    if (*idx < s_state.size())
        return false;                   // existing state

    newState();
    return true;
}        
