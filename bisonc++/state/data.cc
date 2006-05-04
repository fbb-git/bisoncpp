#include "state.ih"

// unsigned State::s_acceptingState;
char const *State::s_stateName[] = 
    {
        "NORMAL",
        "HAS_ERROR_ITEM",   // when an error item is available
        "IS_ERROR_STATE",
    };

unsigned State::s_nShiftReduceConflicts;
unsigned State::s_nReduceReduceConflicts;
vector<State *> State::s_state;

State *State::s_acceptState;
Production const *State::s_startProduction;
