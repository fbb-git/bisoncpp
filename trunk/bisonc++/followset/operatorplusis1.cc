#include "followset.ih"

FollowSet &FollowSet::operator+=(FollowSet const &other) 
{
    d_set.insert(other.d_set.begin(), other.d_set.end());
    d_EOF |= other.d_EOF;

    return *this;
}
