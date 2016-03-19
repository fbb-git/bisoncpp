#include "generator.ih"

void Generator::idOfTag(ostream &out) const
{
    key(out);

    if (d_options.tagMismatches().value == Options::ON)
    {
        out << "char const *idOfTag__[] = {\n";
        for (auto const &poly: d_polymorphic)
            out << "    \"" << poly.first << "\",\n";
        out <<     "    \"<undefined>\"\n"
               "};\n";
    }
}
