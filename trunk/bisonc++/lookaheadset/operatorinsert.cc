#include "lookaheadset.ih"

ostream &operator<<(ostream &out, LookaheadSet const &lookaheadSet)
{
    return lookaheadSet.insert(out);
}
