#include "lookaheadset.ih"

//  Return true if all elements in `other' are already in *this

bool LookaheadSet::operator>=(LookaheadSet const &other) const
{
    return includes(begin(), end(), other.begin(), other.end())
            && 
            (hasEpsilon() || !other.hasEpsilon())
            &&
            (d_EOF || !other.d_EOF);
}
