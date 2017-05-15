#include "generator.ih"

void Generator::ltypeStack(ostream &out) const
{
    if (!d_options.lspNeeded())
        return;

    key(out);

    out << "        std::vector<LTYPE__>      d_locationStack;\n"
           "        LTYPE__  *d_lsp;\n";
}

