#include "parser.ih"

void Parser::setNameSpace()
{
    if (d_scanner.lex() != Scanner::IDENTIFIER)
        lineMsg() << "`%namespace IDENTIFIER' expected" << err;
    else if (!d_nameSpace.size())
        d_nameSpace = d_scanner.text();
}
