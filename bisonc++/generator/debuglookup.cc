#include "generator.ih"

void Generator::debugLookup(std::ostream &out) const
{
    if (!d_genDebug)
        return;

    key(out);

    insert(out, 4, "debuglookup.in");
}
