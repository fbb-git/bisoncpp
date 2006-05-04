#include "item.ih"

Item::Item(Production const *production, unsigned dot)
:
    d_production(production),
    d_dot(dot)
{}
