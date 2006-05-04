#include "state.ih"

void State::showAllStates()
{
    msg() << "\n"
            "GRAMMAR STATES (determined " << s_state.size() << " states)" <<
                                                                        info;

    for_each(s_state.begin(), s_state.end(), showState);
}
