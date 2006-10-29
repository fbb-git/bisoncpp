#include "stateitem.ih"

ostream &StateItem::insertStd(ostream &out) const
{
    return out << d_item;
}

