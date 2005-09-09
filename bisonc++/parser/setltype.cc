#include "parser.ih"

void Parser::setLtype()
{
    if (d_locationDecl.size())
        lineMsg() << "%location-struct or %ltype multiply declared" << err;
    
    d_locationDecl = "typedef ";

    if (d_scanner.lex() == Scanner::IDENTIFIER)
    {
        string const &type = d_scanner.trimmedText();
        if (type.length())
        {
            (d_locationDecl += type) += " LTYPE;\n";
            d_lspNeeded = true;
            return;
        }
    }

   lineMsg() << "`%ltype type-definition' expected" << err;
}



