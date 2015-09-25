#include "firstset.ih"

FirstSet &FirstSet::operator+=(std::set<Element const *> const &terminalSet)
{
    Baseclass::insert(terminalSet.begin(), terminalSet.end());

    return *this;
}
