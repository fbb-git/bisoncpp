#include "generator.ih"

void Generator::ltypePop(ostream &out) const
{
    if (!d_parser.lspNeeded())
        return;

    key(out);

    out << "d_lsp = &d_locationStack[d_stackIdx];\n";
}

