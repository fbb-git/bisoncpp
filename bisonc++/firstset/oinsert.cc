#include "firstset.ih"


ostream &FirstSet::insert(ostream &out) const
{
    out << "{ ";
                                // passing Element const * values
    copy(begin(), end(), ostream_iterator<Element const *>(out, " "));

    if (d_epsilon)
        out << "<e> ";

    out << "}";

    return out;
}
