#include "generator.hh"

void Generator::ltypePush(ostream &out) const
{
    if (!d_options.lspNeeded())
        return;

    key(out);

    out << "*(d_lsp__ = &d_locationStack__[d_stackIdx__]) = d_loc__;\n";
}

