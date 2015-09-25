#include "generator.ih"

void Generator::stype(ostream &out) const
{
    key(out);

    if (!d_options.stype().empty())
        out << d_options.stype() << '\n';
    else
        out << "typedef int STYPE__;\n";
}
