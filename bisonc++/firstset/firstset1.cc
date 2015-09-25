#include "firstset.ih"

FirstSet::FirstSet(Element const *terminal) 
:
    std::set<Element const *>(&terminal, &terminal + 1),
    d_epsilon(false)
{}
