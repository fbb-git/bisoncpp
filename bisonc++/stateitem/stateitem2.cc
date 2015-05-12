#include "stateitem.ih"

StateItem::StateItem(Item const &item)
:
    d_item(item),
    d_next(string::npos)
//    ,
//    d_nextItem(string::npos)
{}
