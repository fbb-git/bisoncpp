#include "generator.ih"

void Generator::baseClass(ostream &out) const
{
    key(out);
    out << "#include \"" << filename(d_options.baseClassHeader()) << "\"\n";
}
