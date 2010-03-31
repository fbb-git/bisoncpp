#include "item.ih"

    // `smaller' for the rule ptr means: pointing to an earlier
    // element in the rules-map.

bool Item::operator==(Item const &other) const
{
    return 
        d_dot == other.d_dot
        &&
        d_production == other.d_production;
}
