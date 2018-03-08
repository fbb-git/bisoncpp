#include "parser.ih"

// unused ruleType is required when initializing s_defaultAction in data.cc

void Parser::blkSTYPE([[maybe_unused]] string const &ruleType, 
                      Production const &prod)
{
    installDefaultAction(prod, s_stype + "{}");
}
