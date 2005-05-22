#include "generator.ih"

void Generator::ltypeData(ostream &out) const
{
    if (!d_parser.lspNeeded())
        return;

    key(out);

    out << "         LTYPE   d_loc;\n"
           "         LTYPE  *d_lsp;\n";
}

