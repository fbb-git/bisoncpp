#include "generator.ih"

void Generator::ltypeData(ostream &out) const
{
    if (!d_options.lspNeeded())
        return;

    key(out);

    insert(out, 8, "ltypedata.in");
}

