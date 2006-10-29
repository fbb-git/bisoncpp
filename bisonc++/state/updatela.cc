#include "state.ih"

// the `parent' is the state from where a transition is performed,
// the `child' is the next state, following a transition.

void State::updateLA(size_t const &parentItemIdx, LookaheadContext &context)
{
    StateItem &parentItem = context.parentItem[parentItemIdx];

    if (parentItem.nextEnlarged())  // the parent's LA was enlarged
    {
                                    // obtain the enlarged LA set for the next
                                    // item of the next state, to be inherited
                                    // from the current state's parent item

                                    // enlarge the LA set of the child State's 
                                    // current kernel item
        if (context.childKernel->enlargeLA(parentItem.lookaheadSet()))
            context.visitChildState = true;

        parentItem.clearNextEnlarged();
    }
    ++context.childKernel;         // next run, visit the next Child's kernel
                                    // item.
}



