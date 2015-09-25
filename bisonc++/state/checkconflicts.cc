#include "state.ih"

// If there are reducible items, SR or RR conflicts may be observed.

// To check for SR conflicts, each reducible item index together with the
// context (consisting of the state's d_itemVector vector and d_nextVector
// vector) is passed to Next's checkShiftReduceConflict member which solves
// the observed shift-reduce conflicts.

// called by: State::define()

void State::checkConflicts()
{
    d_nTransitions = d_nextVector.size();

    if (d_reducible.empty())     // no reductions, no conflicts
        return;

    d_srConflict.inspect();             // detect SR conflicts

                                        // Number of viable transitions:
                                        // reduced by the number of removed
                                        // shifts

//    size_t nremoved = d_srConflict.removeShifts(d_nextVector);
//    cerr << d_nTransitions << ' ' << nremoved << endl;
//    d_nTransitions -= nremoved; //d_srConflict.removeShifts(d_nextVector);

    d_nTransitions -= d_srConflict.removeShifts(d_nextVector);

    d_srConflict.removeReductions(d_itemVector); 



    d_rrConflict.inspect();               // detect RR conflicts

    d_rrConflict.removeConflicts(d_itemVector);

    if (d_reducible.size() > 1)             // more than 1 reduction
        d_stateType.setType(StateType::REQ_TOKEN);
}






