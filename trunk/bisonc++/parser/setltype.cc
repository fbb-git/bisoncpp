#include "parser.ih"

void Parser::setLtype()
{
    if (d_locationDecl.size())
        lineMsg() << "%location-struct or %ltype multiply declared" << err;
    else
    {
        char const *txt = d_scanner.YYText();

        if (strchr(txt, ';'))
            lineMsg() << "`;' in %ltype type-definition `" << txt << "'" << 
                                                                        err;
        else
        { 
            ((d_locationDecl = "typedef ") += txt) += " LTYPE__;\n";
            d_lspNeeded = true;
        }
    }
}



