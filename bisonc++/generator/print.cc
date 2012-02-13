#include "generator.ih"

void Generator::print(ostream &out) const
{
    key(out);

    out << "inline void " << d_options.className() << "::print()\n"
            "{";

    if (!d_print)
        out << "}\n";
    else
        out <<
            "\n"
                    // _UNDETERMINED_ is also used in writer/symbolicnames.cc
            "    enum { _UNDETERMINED_ = -2 };\n"
            "\n"
            "    std::cout << \"Token: \" << symbol__(d_token__) <<\n"
            "                \", text: `\";\n"
            "        if (d_token__ == _UNDETERMINED_)\n"
            "            std::cout << \"'\\n\";\n"
            "        else\n"
            "            std::cout << " << d_matchedTextFunction << 
                                                            " << \"'\\n\";\n"
            "}\n";
}
