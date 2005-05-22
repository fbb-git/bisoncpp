#include "state.ih"

void State::showConflicts() 
{
    unsigned sum = s_nShiftReduceConflicts + s_nReduceReduceConflicts;
    unsigned expected = Rules::expectedConflicts();

    if (sum <= expected)
    {
        if (expected)
            msg() << "\n" <<
                    sum << " (out of max. " << expected << 
                    ") expected conflict(s)" << info;
        return;
    }

    if (s_nShiftReduceConflicts)
        msg() << s_nShiftReduceConflicts << " shift-reduce conflict(s)" << 
                warning;

    if (s_nReduceReduceConflicts)
        msg() << s_nReduceReduceConflicts << " reduce-reduce conflict(s)" <<
                    warning;

    msg() << info;
}
