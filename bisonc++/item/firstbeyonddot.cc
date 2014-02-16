#include "item.ih"

bool Item::firstBeyondDot(FirstSet *firstSet) const
{
                                        // this MUST be dot < size
    for (size_t dot = d_dot + 1, size = productionSize(); dot < size; ++dot)
    {
        *firstSet += (*d_production)[dot].firstSet();

        if (!firstSet->hasEpsilon())    // no more elements if no epsilon in 
            return false;               // the set, return `no epsilon'

        firstSet->rmEpsilon();
    }

    // at this point we've seen all elements beyond dot, and the last one
    // contained epsilon, so more first-elements can be added, and we return 
    // true. An empty set will also return true.

    return true;
}





