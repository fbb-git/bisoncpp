#include "parser.ih"

void Parser::setLtype()
{
    if (d_locationDecl.size())
        lineMsg() << "%location-struct or %ltype multiply declared" << err;
    
    d_locationDecl = "typedef ";

    if (d_scanner.lex() != Scanner::IDENTIFIER)
        lineMsg() << "`%ltype IDENTIFIER' expected" << err;
    else
        (d_locationDecl += d_scanner.text()) += " LTYPE;\n";

    d_lspNeeded = true;
}
