#include "lookaheadset.ih"

LookaheadSet &LookaheadSet::operator+=(LookaheadSet const &other)
{
    *reinterpret_cast<FirstSet *>(this) += other;
    d_EOF |= other.d_EOF;
    return *this;
}
