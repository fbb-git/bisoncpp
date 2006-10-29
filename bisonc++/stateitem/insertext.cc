#include "stateitem.ih"

ostream &StateItem::insertExt(ostream &out) const
{
    out << d_item << "  "  << d_LA << "  " << 
            d_LA_enlarged << ", " << d_nextEnlarged << ", (";

    copy(d_child.begin(), d_child.end(), 
        ostream_iterator<size_t>(out, " "));

    return out << ") " << static_cast<int>(d_next);
}

