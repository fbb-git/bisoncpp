#include "generator.ih"

void Generator::preIncludes(std::ostream &out) const
{
    if (d_options.preInclude().empty())
        return;

    key(out);
    out <<  "#include " << d_options.preInclude() << '\n';
}
