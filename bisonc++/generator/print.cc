#include "generator.ih"

void Generator::print(ostream &out) const
{
    key(out);

                    // _UNDETERMINED_ is also used in writer/symbolicnames.cc

    if (d_printTokens)
        insert(out, 4, "print.in");
}
