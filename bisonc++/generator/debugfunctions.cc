#include "generator.ih"

void Generator::debugFunctions(std::ostream &out) const
{
    if (!d_debug)
        return;

    key(out);

    out << 
        "std::ostream &" << d_baseclassScope << "dflush(std::ostream &out)\n"
        "{\n"
        "    std::ostringstream &s_out = "
                                "dynamic_cast<std::ostringstream &>(out);\n"
        "\n"
        "    std::cout << \"    \" << s_out.str() << std::flush;\n"
        "    s_out.clear();\n"
        "    s_out.str(\"\");\n"
        "    return out;\n"
        "}\n"
        "\n"
        "std::string " << d_baseclassScope << "symbol(int value) const\n"
        "{\n"
        "    using namespace std;\n"
        "    ostringstream ostr;\n"
        "    SMap::const_iterator it = s_symbol.find(value);\n"
        "    if (it != s_symbol.end())\n"
        "        ostr << \"`\" << it->second << \"'\";\n"
        "    else if (isprint(value))\n"
        "        ostr << \"`\" << static_cast<char>(value) << ""\"' "
                                                    "(\" << value << \")\";\n"
        "    else\n"
        "        ostr << \"'\\\\x\" << setfill('0') << hex << setw(2) << "
                                                        "value << \"'\";\n"
        "    return ostr.str();\n"
        "}\n";
}
