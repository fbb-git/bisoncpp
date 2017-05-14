#include "generator.ih"

void Generator::ltypePop(ostream &out) const
{
    if (!d_options.lspNeeded())
        return;

    key(out);

    out << "d_lsp__ = &d_locationStack[d_stackIdx];\n";
}

