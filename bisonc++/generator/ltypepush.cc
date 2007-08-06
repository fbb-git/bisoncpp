#include "generator.ih"

void Generator::ltypePush(ostream &out) const
{
    if (!d_parser.lspNeeded())
        return;

    key(out);

    out << "*(d_lsp__ = &d_locationStack__[d_stackIdx__]) = d_loc__;\n";
}

