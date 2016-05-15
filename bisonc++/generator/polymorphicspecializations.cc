#include "generator.ih"

void Generator::polymorphicSpecializations(ostream &out) const
{
    key(out);

    out <<
        "enum { sizeofTag__ = " << d_polymorphic.size() << " };\n\n";

    if (d_options.tagMismatches().value == Options::ON)
        out << "extern char const *idOfTag__[];\n";

    for (auto &poly: d_polymorphic)
        out << 
            "template <>\n"
            "struct TagOf<" << poly.second << ">\n"
            "{\n"
            "    static Tag__ const tag = Tag__::" << poly.first << ";\n"
            "};\n"
            "\n";

    for (auto &poly: d_polymorphic)
        out << 
            "template <>\n"
            "struct TypeOf<Tag__::" << poly.first << ">\n"
            "{\n"
            "    typedef " << poly.second << " type;\n"
            "};\n"
            "\n";
}









