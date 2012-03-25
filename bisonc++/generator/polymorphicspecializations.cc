#include "generator.ih"

void Generator::polymorphicSpecializations(ostream &out) const
{
    key(out);

    for (auto &poly: d_polymorphic)
        out << 
        "    template <>\n"
        "    struct TagOf<" << poly.second << ">\n"
        "    {\n"
        "        static Tag__ const tag = " << poly.first << ";\n"
        "    };\n"
        "\n";

    for (auto &poly: d_polymorphic)
        out << 
        "    template <>\n"
        "    struct TypeOfBase<" << poly.first << ">\n"
        "    {\n"
        "        typedef " << poly.second << " DataType;\n"
        "    };\n"
        "\n";
}









