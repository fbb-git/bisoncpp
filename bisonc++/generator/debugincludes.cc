#include "generator.ih"

void Generator::debugIncludes(ostream &out) const
{
    if (!d_debug)
        return;

    key(out);

    out <<  "#include <iostream>\n"
            "#include <sstream>\n"
            "#include <string>\n"
            "#include <map>\n";
}
