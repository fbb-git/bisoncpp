#include "generator.ih"

void Generator::ltype(ostream &out) const
{
    if (!d_parser.lspNeeded())
        return;

    key(out);

    if (!d_parser.ltype().empty())
        out << d_parser.ltype() << endl;
    else
        out <<  
            "    struct LTYPE\n"
            "    {\n"
            "        int timestamp;\n"
            "        int first_line;\n"
            "        int first_column;\n"
            "        int last_line;\n"
            "        int last_column;\n"
            "        char *text;\n"
            "    };\n";
}




