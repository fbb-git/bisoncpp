#include "item.ih"

Item::Item(Production const *production, unsigned dot, 
           LookaheadSet const &laSet)
:
    d_production(production),
    d_dot(dot),
    d_lookahead(laSet)
{}
