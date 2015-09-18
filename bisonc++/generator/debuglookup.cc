#include "generator.hh"

void Generator::debugLookup(std::ostream &out) const
{
    if (!d_debug)
        return;

    key(out);

    insert(out, 4, "debuglookup.in");
}
