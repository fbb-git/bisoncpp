#include "lookaheadset.ih"

ostream &LookaheadSet::insert(ostream &out) const
{
    out << "{ ";

    copy(begin(), end(), ostream_iterator<Element const *>(out, " "));

    if (d_EOF)
        out << "<EOF> ";

    out << "}";

    return out;
}
