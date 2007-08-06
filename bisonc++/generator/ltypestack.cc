#include "generator.ih"

void Generator::ltypeStack(ostream &out) const
{
    if (!d_parser.lspNeeded())
        return;

    key(out);

    out << "        std::vector<LTYPE__>      d_locationStack__;\n";
}

