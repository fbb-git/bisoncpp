#include "stateitem.ih"

StateItem::StateItem(Item const &item)
:
    d_item(item),
    d_LA_enlarged(false),
    d_next(string::npos),
    d_nextEnlarged(false)
{}
