#include "itemsets.ih"

// if the item has the symbol to the right of the dot, 
// put the item in the state, moving the dot over to the right of the
// symbol. Return true if this happened at least once, i.e., if state has
// a non-empty kernel-item set.

bool ItemSets::rightOfDot(State *dest, State const &source, 
                                       Symbol const &symbol) 
{
    source.incDot(dest, symbol);

    return dest->kernelSize();
}
