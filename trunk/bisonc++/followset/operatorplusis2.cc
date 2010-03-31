#include "followset.ih"

FollowSet &FollowSet::operator+=(FirstSet const &firstSet) 
{
                                    // As the elements are always Terminals, 
                                    // I can apply a reinterpret_cast here
    auto sourceSet = 
            reinterpret_cast<set<Terminal const *> const *>(&firstSet);

    d_set.insert(sourceSet->begin(), sourceSet->end());

    return *this;
}
