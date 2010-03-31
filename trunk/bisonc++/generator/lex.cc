#include "generator.ih"

void Generator::lex(ostream &out) const
{
    key(out);

    if (!d_print && d_parser.scanner().empty())
        return;

    out << "inline int " << d_parser.className() << "::lex()\n"
            "{\n";

    if (d_print)
        out << "    print();\n";

    out << "    return " << *d_scannerTokenFunction << ";\n"
           "}\n";
}
