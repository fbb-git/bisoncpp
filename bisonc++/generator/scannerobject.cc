#include "generator.ih"

void Generator::scannerObject(ostream &out) const
{
    if (d_options.scannerInclude().empty())
        return;

    key(out);
    out <<  "Scanner d_scanner;\n";
}
