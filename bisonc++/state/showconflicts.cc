#include "state.ih"

void State::showConflicts() 
{
    if (s_nShiftReduceConflicts)
        cout << "\n" << s_nShiftReduceConflicts << " shift-reduce conflict" <<
            (s_nShiftReduceConflicts == 1 ? "" : "s");

    if (s_nReduceReduceConflicts)
        cout << "\n" << s_nReduceReduceConflicts << 
            " reduce-reduce conflict" <<
            (s_nReduceReduceConflicts == 1 ? "" : "s");

    cout << endl;
}
