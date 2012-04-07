#include "generator.ih"

void Generator::polymorphicSpecializations(ostream &out) const
{
    key(out);

    for (auto &poly: d_polymorphic)
        out << 
        "    template <>\n"
        "    struct TagOf<" << poly.second << ">\n"
        "    {\n"
        "        static Tag__ const tag = Tag__::" << poly.first << ";\n"
        "    };\n"
        "\n";

    for (auto &poly: d_polymorphic)
        out << 
        "    template <>\n"
        "    struct TypeOfBase<Tag__::" << poly.first << ">\n"
        "    {\n"
        "        typedef " << poly.second << " DataType;\n"
        "    };\n"
        "\n";
}









