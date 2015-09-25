#include "lookaheadset.ih"

//  Return true if all elements in `other' are already in *this

bool LookaheadSet::operator>=(LookaheadSet const &other) const
{
    return  (hasEpsilon() || !other.hasEpsilon())
            &&
            (d_EOF == e_withEOF || other.d_EOF == e_withoutEOF)
            &&
            includes(begin(), end(), other.begin(), other.end());
}
