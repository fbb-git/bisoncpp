#include "generator.hh"

void Generator::debugDecl(std::ostream &out) const
{
    if (!d_debug && !d_printTokens)
        return;

    key(out);

    insert(out, 8, "debugdecl.in");
}
