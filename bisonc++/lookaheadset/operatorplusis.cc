#include "lookaheadset.ih"

LookaheadSet &LookaheadSet::operator+=(LookaheadSet const &other)
{
    *reinterpret_cast<FirstSet *>(this) += other;

    if (other.d_EOF == e_withEOF)
        d_EOF = e_withEOF;

    return *this;
}
