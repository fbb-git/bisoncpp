#include "generator.ih"

void Generator::baseClassCode(ostream &out) const
{
    key(out);

    out << "d_requiredTokens_(" << d_options.requiredTokens() << ")\n"
           "{\n";

    if (d_options.polymorphic())
        out << "    Meta_::t_nErrors = &d_nErrors_;\n";
}   
