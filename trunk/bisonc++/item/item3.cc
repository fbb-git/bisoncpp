#include "item.ih"

Item::Item(Production const *production, size_t dot)
:
    d_production(production),
    d_dot(dot)
{
    d_production->used();
}
