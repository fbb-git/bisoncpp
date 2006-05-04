#include "followset.ih"

ostream &FollowSet::ostrInsert(ostream &out) const
{
    out << "{ ";

    copy(begin(), end(), ostream_iterator<Element const *>(out, " "));

    if (d_EOF)
        out << "<EOF> ";

    out << "}";

    return out;
}
