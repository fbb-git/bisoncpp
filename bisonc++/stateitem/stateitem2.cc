#include "stateitem.ih"

StateItem::StateItem(Item const &item)
:
    d_item(item),
    d_nextIdx(string::npos)
{}
