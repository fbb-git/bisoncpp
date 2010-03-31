#include "generator.ih"

void Generator::print(ostream &out) const
{
    key(out);

    out << "inline void " << d_parser.className() << "::print()\n"
            "{";

    if (!d_print)
        out << "}\n";
    else
        out <<
            "\n"
            "    std::cout << \"Token: \" << symbol__(d_token__) <<\n"
            "                \", text: `\" << "  << 
                                                    *d_matchedTextFunction <<
                                                    " << \"'\\n\";\n"
            "}\n";
}
