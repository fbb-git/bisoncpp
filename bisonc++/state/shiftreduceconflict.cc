#include "state.ih"

void State::shiftReduceConflict(string const &tokenName, 
                                unsigned nextStateIdx,
                                Production const *production) 
{
    ++s_nShiftReduceConflicts;
    ++d_nShiftReduceConflicts;

    msg() << "\n"
            "    Shift-reduce conflict on " << tokenName << ":\n"
            "    shift to state " << nextStateIdx << "\n"
            "    [or reduce, using production\n" << 
            "       " << production << "]\n" 
            "    Conflict solved using (default) shift" << info;
}


