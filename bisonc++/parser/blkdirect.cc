#include "parser.ih"

void Parser::blkDirect(string const &ruleType, Production const &prod)
{
    installDefaultAction(prod, svsElement(prod.size(), 1) );
}
