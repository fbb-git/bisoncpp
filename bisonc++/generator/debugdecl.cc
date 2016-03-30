#include "generator.ih"

void Generator::debugDecl(std::ostream &out) const
{
    if (!d_genDebug && !d_printTokens)
        return;

    key(out);

    insert(out, 8, "debugdecl.in");
}
