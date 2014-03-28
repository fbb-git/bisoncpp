#include "generator.ih"

void Generator::ltype(ostream &out) const
{
    if (!d_options.lspNeeded())
        return;

    key(out);

    insert(out, 4, "ltype.in");
}




