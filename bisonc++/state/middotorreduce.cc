#include "state.ih"

void State::midDotOrReduce(Item &item, MDORContext &context)
{
    if (item.dot() < item.production().size())    // trailing dot ?
        *context.onlyTrailingDots = false;         // no
    else                             // yes, maybe reduce using some rule
        context.obj.reduce(item); 
}
