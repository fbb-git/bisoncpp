#include "firstset.ih"

FirstSet &FirstSet::operator+=(FirstSet const &other)
{
    *this += other.set();
    d_epsilon |= other.d_epsilon;
    return *this;
}
