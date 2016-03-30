#include "generator.ih"

void Generator::debugFunctions(std::ostream &out) const
{
    bool verbose = d_arg.option(0, "error-verbose");

    if (not d_genDebug && not verbose && not d_printTokens)
        return;

    key(out);

    if (d_genDebug)
        insert(out, 0, "debugfunctions1.in");

    if (d_genDebug || d_printTokens)
        insert(out, 0, "debugfunctions2.in");

    if (verbose)
        insert(out, 0, "debugfunctions3.in");
}
