#include "parser.ih"

// unused ruleType is required when initializing s_defaultAction in data.cc

void Parser::blkDirect([[maybe_unused]] string const &ruleType, 
                       Production const &prod)
{
    installDefaultAction(prod, svsElement(prod.size(), 1) );
}
