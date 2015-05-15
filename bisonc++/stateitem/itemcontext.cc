#include "stateitem.ih"

// Produces:
//  item - LA - children - next-index

ostream &StateItem::itemContext(ostream &out) const
{
    out << d_item << "  "  << d_LA << ", (";

    copy(d_child.begin(), d_child.end(), 
        ostream_iterator<size_t>(out, " "));

    return out << ") " << static_cast<int>(d_next);
}

