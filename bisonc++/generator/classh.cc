#include "generator.ih"

void Generator::classH(ostream &out) const
{
    key(out);
    out << "#include \"" << filename(d_options.classHeader()) << "\"\n";
}
