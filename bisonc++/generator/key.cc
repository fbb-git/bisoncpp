#include "generator.ih"

void Generator::key(ostream &out) const
{
    out << setw(d_indent) << "" << "// $insert " << d_key << '\n' <<
            setw(d_indent) << "" << flush;
}
