#include "generator.ih"

void Generator::ltypeData(ostream &out) const
{
    if (!d_parser.lspNeeded())
        return;

    key(out);

    out << "         LTYPE__   d_loc__;\n"
           "         LTYPE__  *d_lsp__;\n";
}

