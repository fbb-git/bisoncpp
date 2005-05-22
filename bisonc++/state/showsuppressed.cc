#include "state.ih"

void State::showSuppressed() const
{
    if (d_suppressed.empty())
        return;

    msg() << "\n"
            "    Actions suppressed by the default conflict resolution "
            "procedures:" << info;

    for                         // first is Terminal const *
    (                           // second is ShiftReduce
        ActionTableConstIter it = d_suppressed.begin();
            it != d_suppressed.end();
                ++it
    )
        showAction(it->first, it->second, true);
}

