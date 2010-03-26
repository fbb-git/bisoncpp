#include "generator.ih"

void Generator::lex(ostream &out) const
{
    key(out);

    if (d_parser.scanner().empty())
        return;

    out << "inline int " << d_parser.className() << "::lex()\n"
            "{\n";

    if (!d_arg.option('t'))
        out << "    return " << d_parser.scannerFunction() << ";\n"
               "}\n";
    else
    {
        out << 
        "    int ret = " << d_parser.scannerFunction() << ";\n"
        "    std::string const &sym = symbol(ret);\n"
        "\n"
        "    std::cout << \"token \" << sym;\n"
        "    if (sym[1] == '\\\\')\n"
        "        std::cout << '\n';\n"
        "    else\n"
        "        std::cout << \": `\" << " << d_parser.matchFunction() << 
                                                          " << '\\n';\n"
        "    return ret;\n"
        "}\n";
    }   
}
