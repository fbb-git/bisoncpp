#include "lookaheadset.ih"

void LookaheadSet::listElements(ostream &out, char const *sep) const
{
    copy(begin(), end(), ostream_iterator<Element const *>(out, sep));
}
