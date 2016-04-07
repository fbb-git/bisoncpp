#include "parser.ih"

void Parser::blkSTYPE(string const &ruleType, Production const &prod)
{
    installDefaultAction(prod, s_stype + "{}");
}
