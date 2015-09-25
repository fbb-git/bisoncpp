#include "lookaheadset.ih"

LookaheadSet &LookaheadSet::operator-=(LookaheadSet const &other)
{
    std::set<Element const *> difference;

    set_difference(begin(), end(), other.begin(), other.end(),
                    inserter(difference, difference.begin()));

    *reinterpret_cast<std::set<Element const *> *>(this) = difference;

    if (other.d_EOF == e_withEOF)
        d_EOF = e_withoutEOF;

    return *this;
}
