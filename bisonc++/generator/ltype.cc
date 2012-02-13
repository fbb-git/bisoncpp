#include "generator.ih"

void Generator::ltype(ostream &out) const
{
    if (!d_options.lspNeeded())
        return;

    key(out);

    if (!d_options.ltype().empty())
        out << d_options.ltype() << '\n';
    else
        out <<  
            "    struct LTYPE__\n"
            "    {\n"
            "        int timestamp;\n"
            "        int first_line;\n"
            "        int first_column;\n"
            "        int last_line;\n"
            "        int last_column;\n"
            "        char *text;\n"
            "    };\n";
}




