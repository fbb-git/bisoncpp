#include "firstset.ih"

FirstSet &FirstSet::operator+=(FirstSet const &other)
{
    *this += static_cast<set<Element const *> const &>(other);
    d_epsilon |= other.d_epsilon;
    return *this;
}
