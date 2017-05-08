#include "generator.ih"

void Generator::baseClassCode(ostream &out) const
{
    key(out);

    out << "d_requiredTokens__(" << d_options.requiredTokens() << ")\n"
           "{\n";

    if (d_options.polymorphic())
        out << "    Meta__::t_nErrors = &d_nErrors__;\n";
}   
