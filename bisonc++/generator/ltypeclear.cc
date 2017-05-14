#include "generator.ih"

void Generator::ltypeClear(ostream &out) const
{
    if (!d_options.lspNeeded())
        return;

    key(out);

    out << "d_locationStack.clear();\n";
}

