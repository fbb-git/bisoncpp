#include "state.ih"

void State::defineActions()
{
    for_each(s_state.begin(), s_state.end(), defineStateActions);
}
