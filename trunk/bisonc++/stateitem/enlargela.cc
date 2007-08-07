#include "stateitem.ih"

bool StateItem::enlargeLA(LookaheadSet const &parentLA)
{
    if (d_LA >= parentLA)       // no additions needed
        return false;

    d_LA += parentLA;           // enlarge the LA set
    d_LA_enlarged = true;       // and raise the flag

    return true;
}
