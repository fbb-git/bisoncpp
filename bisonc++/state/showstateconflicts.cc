#include "state.ih"

void State::showStateConflicts(State const *pState)
{
    if (!pState->d_nShiftReduceConflicts && !pState->d_nReduceReduceConflicts)
        return;

    msg() << "State " << pState->d_idx << " has " << spool;

    if (pState->d_nShiftReduceConflicts)
        msg() << pState->d_nShiftReduceConflicts << 
                " shift-reduce conflict(s)" << spool;

    if (pState->d_nReduceReduceConflicts)
    {
        if (pState->d_nShiftReduceConflicts)
            msg() << " and " << spool;

        msg() << pState->d_nReduceReduceConflicts << 
                " reduce-reduce conflict(s)" << spool;
    }

    msg() << info;        
}
