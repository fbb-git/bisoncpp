#include "state.ih"

    // must use Item const &item as first parameter, rather than using return 
    // by argument, since `item' is used as the first argument by for_each()
    // 
    // If the item has symbol at its dot position, then a new item is
    // constructed having an incremented dot position. This items is then
    // added to the destination state.

void State::inspectItem(Item const &item, IIContext &context)
{
    if (item.hasRightOfDot(context.symbol))
        *context.dest += item.incDot();
}
