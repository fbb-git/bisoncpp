#include "generator.ih"

void Generator::baseClass(ostream &out) const
{
    key(out);
    out << "#include \"" << d_options.baseClassHeader() << "\"\n";
}
