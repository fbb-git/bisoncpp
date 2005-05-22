#include "parser.ih"

void Parser::setClassName()
{
    if (d_scanner.lex() != Scanner::IDENTIFIER)
        lineMsg() << "`%class-name IDENTIFIER' expected" << err;
    else if (d_className.size())
        lineMsg() << "%class-name multiply declared" << err;
    else
        d_className = d_scanner.text();
}
