#include "followset.ih"

// Can't use insert since it would shadow set's insert() member
ostream &FollowSet::oInsert(ostream &out) const
{
    out << "{ " << OM::std;

    copy(begin(), end(), ostream_iterator<Element const *>(out, " "));

    if (d_EOF)
        out << "<EOF> ";

    out << "}";

    return out;
}
