#include "generator.ih"

void Generator::namespaceOpen(std::ostream &out) const
{
    if (d_nameSpace.empty())
        return;

    key(out);
    out <<  "namespace " << d_nameSpace << "\n"
            "{\n";
}
