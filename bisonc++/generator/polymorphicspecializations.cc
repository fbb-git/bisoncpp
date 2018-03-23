#include "generator.ih"

void Generator::polymorphicSpecializations(ostream &out) const
{
    key(out);

    out <<
        "enum { sizeofTag_ = " << d_polymorphic.size() << " };\n\n";

    if (d_options.tagMismatches().value == Options::ON)
        out << "extern char const *idOfTag_[];\n";

    for (auto &poly: d_polymorphic)
        out << 
            "template <>\n"
            "struct TagOf<" << poly.second << ">\n"
            "{\n"
            "    static Tag_ const tag = Tag_::" << poly.first << ";\n"
            "};\n"
            "\n";

    for (auto &poly: d_polymorphic)
        out << 
            "template <>\n"
            "struct TypeOf<Tag_::" << poly.first << ">\n"
            "{\n"
            "    typedef " << poly.second << " type;\n"
            "};\n"
            "\n";
}









