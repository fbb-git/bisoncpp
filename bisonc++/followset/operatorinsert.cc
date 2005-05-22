#include "followset.ih"

ostream &operator<<(ostream &out, FollowSet const &followSet)
{
    return followSet.ostrInsert(out);
}
