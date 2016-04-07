#include "parser.ih"

void Parser::blkAssignW(string const &ruleType, Production const &prod)
{
    warnDefaultAction(prod);
    blkAssign(ruleType, prod);
}
