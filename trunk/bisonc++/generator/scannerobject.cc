#include "generator.ih"

void Generator::scannerObject(ostream &out) const
{
    if (d_parser.scanner().empty())
        return;

    key(out);
    out <<  "Scanner d_scanner;\n";
}
