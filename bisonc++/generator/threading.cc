#include "generator.hh"

void Generator::threading(ostream &out) const
{
    key(out);

    insert(out, 4, "threading.in");
}








