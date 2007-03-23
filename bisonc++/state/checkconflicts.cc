#include "state.ih"

// If there are any reducible items, SR or RR conflicts may be observed.

// To check for SR conflict, pass each reducible item index together with the
// context consisting of the state's d_itemVector vector and d_nextVector
// vector to Next's checkShiftReduceConflict member which will solve all
// observed shift-reduce conflicts.

void State::checkConflicts() 
{
    d_nTransitions = d_nextVector.size();

    if (d_reducible.empty())     // no reductions, no conflicts
        return;

    d_srConflict.inspect();             // detect SR conflicts

                                        // Number of viable transitions:
                                        // reduced by the number of removed
                                        // shifts
    d_nTransitions -= d_srConflict.removeShifts(d_nextVector);

    d_srConflict.removeReductions(d_itemVector); 

    d_rrConflict.inspect();               // detect RR conflicts

    d_rrConflict.removeConflicts(d_itemVector);

    if (d_reducible.size() > 1)             // more than 1 reduction
        setType(NEEDS_LOOKAHEAD);
}
