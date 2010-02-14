#include "generator.ih"

void Generator::preIncludes(std::ostream &out) const
{
    if (d_parser.preInclude().empty())
        return;

    key(out);
    out <<  "#include " << d_parser.preInclude() << '\n';
}
