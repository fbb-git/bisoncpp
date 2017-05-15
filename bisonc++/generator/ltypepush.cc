#include "generator.ih"

void Generator::ltypePush(ostream &out) const
{
    if (!d_options.lspNeeded())
        return;

    key(out);

    out << "*(d_lsp = &d_locationStack[d_stackIdx]) = d_loc__;\n";
}

