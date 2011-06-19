#include "state.ih"

void State::distributeLA(Next &next, LookaheadContext &context)
{
    State *childState = s_state[next.next()];

    context.childKernel = childState->d_itemVector.begin();
    context.visitChildState = false;

        // visit all kernel items of the child state
    for_each(
        next.kernel().begin(), next.kernel().end(),
        [&](size_t itemIdx)
        {
            updateLA(itemIdx, context);
        }
    );

        // if the child's state has its LA changed, make sure it's visited
    if (context.visitChildState)
        context.child.push_back(childState);
}
