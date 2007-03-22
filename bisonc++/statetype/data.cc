#include "statetype.ih"

char const *StateType::s_stateName[] = 
    {
        "NORMAL",
        "HAS_ERROR_ITEM",   // when an error item is available
        "ERROR_STATE",
    };

