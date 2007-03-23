#include "statetype.ih"

char const *StateType::s_stateName[] = 
    {
        "NORMAL",
        "HAS_ERROR_ITEM",   // when an error item is available
        "ERROR_STATE",      // Info: (in)directly derived from _error_
        "NEEDS_LOOKAHEAD"   // State containing multiple reductions
    };

