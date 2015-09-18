#include "generator.hh"

void Generator::namespaceClose(std::ostream &out) const
{
    if (d_nameSpace.empty())
        return;

    key(out);
    out <<  "}\n";
}
