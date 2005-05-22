#include "generator.ih"

void Generator::stype(ostream &out) const
{
    key(out);

    if (!d_parser.stype().empty())
        out << d_parser.stype() << endl;
    else
        out <<  
            "    typedef int STYPE;\n";
}
