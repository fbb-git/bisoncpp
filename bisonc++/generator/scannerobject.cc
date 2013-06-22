#include "generator.ih"

void Generator::scannerObject(ostream &out) const
{
    if (d_options.scannerInclude().empty())
        return;

    key(out);
    out <<  d_options.scannerClassName() << "Scanner d_scanner;\n";
}
