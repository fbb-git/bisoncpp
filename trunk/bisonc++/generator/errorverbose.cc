#include "generator.ih"

void Generator::errorVerbose(ostream &out) const
{
    if (!d_arg.option(0, "error-verbose"))
        return;

    key(out);
    out << "errorVerbose__();\n";
}
