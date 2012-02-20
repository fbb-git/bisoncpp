#include "parser.ih"

void Parser::storeIdent()
{
    d_lastIdent = d_scanner.matched();
}
