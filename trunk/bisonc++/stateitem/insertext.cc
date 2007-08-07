#include "stateitem.ih"

// Produces:
//  item - LA - LA-enlarged - next-enlarged - children - next-index

ostream &StateItem::insertExt(ostream &out) const
{
    out << d_item << "  "  << d_LA << "  " << d_nextEnlarged << ", (";

    copy(d_child.begin(), d_child.end(), 
        ostream_iterator<size_t>(out, " "));

    return out << ") " << static_cast<int>(d_next);
}

