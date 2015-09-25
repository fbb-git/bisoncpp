#include "lookaheadset.ih"

LookaheadSet &LookaheadSet::operator+=(FirstSet const &firstSet)
{
    *reinterpret_cast<FirstSet *>(this) += firstSet;
    return *this;
}
