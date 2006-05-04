#include "followset.ih"

FollowSet &FollowSet::operator+=(FollowSet const &other) 
{
    insert(other.begin(), other.end());
    d_EOF |= other.d_EOF;

    return *this;
}
