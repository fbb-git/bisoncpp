#include "firstset.ih"

ostream &operator<<(ostream &out, FirstSet const &firstSet)
{
    return firstSet.insert(out);
}
