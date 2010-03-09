#include "followset.ih"

// Can't use insert since it would shadow set's insert() member
ostream &FollowSet::oInsert(ostream &out) const
{
    out << "{ ";

    Terminal::inserter(&Terminal::plainName);

    copy(d_set.begin(), d_set.end(), 
                            ostream_iterator<Element const *>(out, " "));

    Terminal::inserter(&Terminal::valueQuotedName);

    if (d_EOF)
        out << "<EOF> ";

    out << "}";

    return out;
}
