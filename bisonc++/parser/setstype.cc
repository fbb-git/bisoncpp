#include "parser.ih"

void Parser::setStype()
{
    if (d_stackDecl.size())
        lineMsg() << "%union or %stype multiply declared" << err;
    
    d_stackDecl = "typedef ";

    if (d_scanner.lex() != Scanner::IDENTIFIER)
        lineMsg() << "`%stype IDENTIFIER' expected" << err;
    else
        (d_stackDecl += d_scanner.text()) += " STYPE;\n";
}
