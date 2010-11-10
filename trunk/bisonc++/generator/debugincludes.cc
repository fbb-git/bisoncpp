#include "generator.ih"

void Generator::debugIncludes(ostream &out) const
{
    bool verbose = d_arg.option(0, "error-verbose");

    if (!d_debug && !verbose && !d_print)
        return;

    key(out);

    if (d_debug)
        out <<  "#include <iostream>\n"
                "#include <sstream>\n"
                "#include <string>\n"
                "#include <map>\n";

    out <<  "#include <iomanip>\n";
}
