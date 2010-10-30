#include "parser.ih"

void Parser::setStype()
{
    if (d_stackDecl.size())
        lineMsg(emsg) << "%union or %stype multiply specified" << endl;
    else
    {
        char const *txt = d_scanner.YYText();

        if (strchr(txt, ';'))
            lineMsg(emsg) << "`;' in %stype type-definition `" << txt << 
                                                                '\'' << endl;
        else
            ((d_stackDecl = "typedef ") += txt) += " STYPE__;\n";
    }
}
