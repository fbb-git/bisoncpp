#include "item.ih"

Item::Item(Item const *item, size_t dot)
:
    d_production(item->d_production),
    d_dot(dot)
{}
