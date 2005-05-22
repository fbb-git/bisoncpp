#include "generator.ih"

void Generator::lex(ostream &out) const
{
    key(out);

    out << "int lex()";

    if (d_parser.scanner().empty())
    {
        out << ";\n";
        return;
    }
    

    out <<  "\n" <<
            setw(d_indent) << "" << 
                                    "{\n" <<
            setw(d_indent) << "" << 
                                    "    return d_scanner.yylex();\n" <<
            setw(d_indent) << "" << 
                                    "}\n";
}
