#include "generator.ih"

void Generator::polyIncludes(ostream &out) const
{
    if (not d_options.polymorphic())
        return;

    key(out);

    out << "#include <memory>\n";
}
