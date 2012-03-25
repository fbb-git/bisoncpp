#include "generator.ih"

void Generator::polymorphic(ostream &out) const
{
    if (not d_options.polymorphic())
        return;

    key(out);

    out << 
        "enum Tag__\n"                            // Tags
        "{\n";

    for (auto &poly: d_polymorphic)
        out << "    " << poly.first << ",\n";

    out << 
        "};\n"
        "\n";


    ifstream in;
    Errno::open(in,  d_options.polymorphicSkeleton()); 

    filter(in, out, false);
}









