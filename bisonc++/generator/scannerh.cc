#include "generator.ih"

void Generator::scannerH(ostream &out) const
{
    if (d_options.scannerInclude().empty())
        return;

    key(out);
    out <<  "#include " << d_options.scannerInclude() << '\n';
}
