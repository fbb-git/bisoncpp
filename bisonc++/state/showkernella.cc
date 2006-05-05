#include "state.ih"

void State::showKernelLA(Item const &item, TransitionMap &transmap)
{
    msg() << indent << spool;
    Item::showKernel(item);
    msg() << ", LA " << transmap[item.lhs()]->lookaheadSet() << info;
}
