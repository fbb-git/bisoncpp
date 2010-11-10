#include "generator.ih"

void Generator::ltypeResize(ostream &out) const
{
    if (!d_parser.lspNeeded())
        return;

    key(out);

    out << "d_locationStack__.resize(newSize);\n";
}

