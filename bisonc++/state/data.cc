#include "state.ih"

unsigned State::s_acceptingState;
unsigned State::s_nShiftReduceConflicts;
unsigned State::s_nReduceReduceConflicts;
char const *State::s_stateName[] = 
    {
        "NORMAL",
        "HAS_ERROR_ITEM",   // when an error item is available
        "IS_ERROR_STATE",
    };

