#include "generator.ih"

void Generator::scannerH(ostream &out) const
{
    if (d_parser.scanner().empty())
        return;

    key(out);
    out <<  "#include " << d_parser.scanner() << '\n';
}
