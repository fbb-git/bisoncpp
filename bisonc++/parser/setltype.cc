#include "parser.ih"

void Parser::setLtype()
{
    if (d_locationDecl.size())
        lineMsg(emsg) << "%location-struct or %ltype multiply declared" << 
                                                                        endl;
    else
    {
//        char const *txt = d_scanner.YYText();
        string const &txt = d_scanner.YYText();

//        if (strchr(txt, ';'))
        if (txt.find(';') != string::npos)
            lineMsg(emsg) << "`;' in %ltype type-definition `" << txt << 
                                                                '\'' << endl;
        else
        { 
            ((d_locationDecl = "typedef ") += txt) += " LTYPE__;\n";
            d_lspNeeded = true;
        }
    }
}



