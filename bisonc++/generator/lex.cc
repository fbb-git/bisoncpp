#include "generator.ih"

void Generator::lex(ostream &out) const
{
    key(out);

    if (!d_displayTokens && d_options.scannerInclude().empty())
        return;

    out << "inline int " << d_options.className() << "::lex()\n"
            "{\n";

    if (d_displayTokens)
        out << "    print();\n";

    out << "    return " << d_tokenFunction << ";\n"
           "}\n";
}
