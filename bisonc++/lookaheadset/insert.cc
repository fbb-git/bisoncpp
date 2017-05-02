#include "lookaheadset.ih"

ostream &LookaheadSet::insert(ostream &out) const
{
    out << "{ ";

    listElements(out);

    if (d_EOF == e_withEOF)
        out << "<EOF> ";

    out << "}";

    return out;
}
