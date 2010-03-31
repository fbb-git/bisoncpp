#include "item.ih"

    // return true if the current item is the predecessor of 
    // the next item. So, their rules are identical, but
    // the current item's dot position is one lower than the 
    // the next item's dot position.

bool Item::transitsTo(Item const &next) const
{
    return 
        d_dot + 1 == next.d_dot
        &&
        d_production == next.d_production;
}
