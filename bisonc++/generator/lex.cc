#include "generator.ih"

void Generator::lex(ostream &out) const
{
    key(out);

    if (d_parser.scanner().empty())
        return;

    out << "inline int " << d_parser.className() << "::lex()\n"
            "{\n"
            "    return d_scanner.yylex();\n"
            "}\n";
}
