#include "item.ih"

Item::Item(Production const *start)
:
    d_production(start),
    d_dot(0)            // In this item we haven't as yet seen any part of the 
                        // production rule.
{
    d_production->used();
}
