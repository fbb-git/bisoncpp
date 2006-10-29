#include "stateitem.ih"

// LA propagation proceeds as follows: When a stateitem X has its LA_enlarged
// flag set:
//      Set its nextEnlarged flag
//      Lower its LA_enlarged flag
//      Visit its child items. The children will be called with a proposed LA
// set which is equal to the first-set of their parent's production rule
// beyond the current dot. If this proposed LA set contains <epsilon> it is
// augmented with the parent's LA set itself.


bool StateItem::propagateLA(StateItem &stateItem, Vector &vector)
{
    if (!stateItem.d_LA_enlarged)
        return false;

    stateItem.d_LA_enlarged = false;
    stateItem.d_nextEnlarged = true;
    
    PropContext context = 
    {
        vector,
        LookaheadSet()
    };

    if (stateItem.d_item.firstBeyondDot(&context.proposedLA))
        context.proposedLA += stateItem.d_LA;

    for_each(stateItem.d_child.begin(), stateItem.d_child.end(), 
        Wrap1c<size_t, PropContext>(propagate, context));

    return true;
}
