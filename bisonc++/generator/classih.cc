#include "generator.ih"

void Generator::classIH(ostream &out) const
{
    key(out);
    out << "#include \"" << 
                filename(d_options.implementationHeader()) << "\"\n";
}
