#include "generator.ih"

void Generator::ltypeStack(ostream &out) const
{
    if (!d_options.lspNeeded())
        return;

    key(out);

    out << "        std::vector<LTYPE_>      d_locationStack;\n"
           "        LTYPE_  *d_lsp;\n";
}

