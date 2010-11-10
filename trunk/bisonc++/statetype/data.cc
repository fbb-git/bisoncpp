#include "statetype.ih"

char const *StateType::s_stateName[] = 
    {
        "NORMAL",               // 0
        "ERR_ITEM",             // 1: state has an error item
        "REQ_TOKEN",            // 2: needs token at terminal shifts and
                                //    multiple reductions
        "ERR_REQ",              // 3
        "DEF_RED",              // 4: state has a default reduction
        "ERR_DEF",              // 5: 1 | 4
        "REQ_DEF",              // 6: 2 | 4
        "ERR_REQ_DEF"           // 7: 1 | 2 |4
    };

