#include "stateitem.ih"

// Produces:
//  item - LA - next-index

ostream &StateItem::itemContext(ostream &out) const
{
    return out << d_item << "  "  << d_LA << "  " << 
                                            static_cast<int>(d_nextIdx);
}

