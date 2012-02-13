#include "generator.ih"

void Generator::classH(ostream &out) const
{
    key(out);
    out << "#include \"" << d_options.classHeader() << "\"\n";
}
