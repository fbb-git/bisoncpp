#include "state.ih"

void State::showActions() const
{
    for                         // first is Terminal const *
    (                           // second is ShiftReduce
        ActionTableConstIter it = d_action.begin();
            it != d_action.end();
                ++it
    )
    {
        ShiftReduce const &action = it->second;

        if (action.production() != d_defaultReduction)
            showAction(it->first, action);
    }
}
