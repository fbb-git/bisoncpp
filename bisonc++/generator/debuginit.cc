#include "generator.ih"

void Generator::debugInit(ostream &out) const
{
    key(out);
    out << "d_debug(" << boolalpha << d_debug << "),\n";
}   
