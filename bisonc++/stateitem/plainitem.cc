#include "stateitem.ih"

ostream &StateItem::plainItem(ostream &out) const
{
    return out << d_item;
}

