#include "stateitem.ih"

// Visit element idx of the stateitem vector, which is a child-production 
// rule of the rule handled at propagateLA. 

// If the proposed (proposedLA) LA set contains additional elements, set the
// d_LA_enlarged flag, and add the new elements to the current item's LA set.

void StateItem::propagate(size_t &idx, PropContext &context)
{
    StateItem &itemIdx = context.vector[idx];

                                        // The current LA does not contain
                                        // its new LA:
    if (!(itemIdx.d_LA >= context.proposedLA))  
    {
        itemIdx.d_LA_enlarged = true;   // enlarged LA set;
        itemIdx.d_LA += context.proposedLA;// add new items
    }
}





