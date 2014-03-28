#include "generator.ih"

void Generator::debugIncludes(ostream &out) const
{
    bool verbose = d_arg.option(0, "error-verbose");

    if (!d_debug && !verbose && !d_printTokens)
        return;

    key(out);

    insert(out, 0, "debugincludes.in");
}
