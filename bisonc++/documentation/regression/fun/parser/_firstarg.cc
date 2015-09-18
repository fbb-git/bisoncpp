#include "parser.hh"

RuleValue Parser::firstArg(RuleValue &rv)
{
    return RuleValue(new vector<RuleValue>(1, rv));
}
