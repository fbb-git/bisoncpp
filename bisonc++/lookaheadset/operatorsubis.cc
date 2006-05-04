#include "lookaheadset.ih"

LookaheadSet &LookaheadSet::operator-=(LookaheadSet const &other)
{
    std::set<Element const *> difference;

    set_difference(begin(), end(), other.begin(), other.end(),
                    inserter(difference, difference.begin()));

    *reinterpret_cast<std::set<Element const *> *>(this) = difference;
    d_EOF &= !other.d_EOF;

    return *this;
}
