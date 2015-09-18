#include "parser.hh"

void Parser::storeIdent()
{
    d_lastIdent = d_scanner.matched();
}
