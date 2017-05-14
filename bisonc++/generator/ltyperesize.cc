#include "generator.ih"

void Generator::ltypeResize(ostream &out) const
{
    if (!d_options.lspNeeded())
        return;

    key(out);

    out << "d_locationStack.resize(newSize);\n";
}

