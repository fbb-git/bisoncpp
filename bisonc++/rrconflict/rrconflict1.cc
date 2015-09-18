#include "rrconflict.hh"

RRConflict::RRConflict(StateItem::Vector const &stateItem, 
                       vector<size_t> const &reducible)
:
    d_itemVector(stateItem),
    d_reducible(reducible)
{
}
