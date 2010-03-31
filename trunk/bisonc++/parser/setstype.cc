#include "parser.ih"

void Parser::setStype()
{
    if (d_stackDecl.size())
        lineMsg() << "%union or %stype multiply specified" << err;
    else
    {
        char const *txt = d_scanner.YYText();

        if (strchr(txt, ';'))
            lineMsg() << "`;' in %stype type-definition `" << txt << "'" << 
                                                                        err;
        else
            ((d_stackDecl = "typedef ") += txt) += " STYPE__;\n";
    }
}
