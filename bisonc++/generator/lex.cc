#include "generator.ih"

void Generator::lex(ostream &out) const
{
    key(out);

    if (d_printTokens || not d_options.implementationHeader().empty())
        insert(out, "lex.in");
}
