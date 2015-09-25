#include "srconflict.ih"

SRConflict::SRConflict(Next::Vector const &nextVector, 
                        StateItem::Vector const &itemVector, 
                        std::vector<size_t> const &reducible)
:
    d_nextVector(nextVector),
    d_itemVector(itemVector),
    d_reducible(reducible)   
{}
