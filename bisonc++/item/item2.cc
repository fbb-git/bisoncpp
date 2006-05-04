#include "item.ih"

Item::Item(Item const *item, unsigned dot)
:
    d_production(item->d_production),
    d_dot(dot)
{}
