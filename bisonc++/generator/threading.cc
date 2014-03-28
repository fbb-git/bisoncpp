#include "generator.ih"

void Generator::threading(ostream &out) const
{
    key(out);

    insert(out, 0, "threading.in");
}








