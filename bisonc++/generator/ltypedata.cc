#include "generator.ih"

void Generator::ltypeData(ostream &out) const
{
    if (!d_options.lspNeeded())
        return;

    key(out);

    out << "         LTYPE__   d_loc__;\n"
           "         LTYPE__  *d_lsp__;\n";
}

