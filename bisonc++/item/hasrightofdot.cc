#include "item.ih"

bool Item::hasRightOfDot(Symbol const &symbol) const
{
    return 
        d_dot < d_production->size()        // dot position before the end
        &&                                  // and
        d_production->rhs(d_dot) == &symbol; // symbol is at the . position 
}

