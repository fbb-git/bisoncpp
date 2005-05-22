#include "lookaheadset.ih"

bool LookaheadSet::operator>=(LookaheadSet const &other) const
{
    return includes(begin(), end(), other.begin(), other.end())
            && 
            (hasEpsilon() || !other.hasEpsilon())
            &&
            (d_EOF || !other.d_EOF);
}
