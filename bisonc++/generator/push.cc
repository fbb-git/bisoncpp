#include "generator.ih"

void Generator::push(ostream &out) const
{
    key(out);

    if (d_genDebug)
        insert(out, 4, "push.in");
}
