#include "generator.hh"

void Generator::classHH(ostream &out) const
{
    key(out);
    out << "#include \"" << 
                filename(d_options.implementationHeader()) << "\"\n";
}
