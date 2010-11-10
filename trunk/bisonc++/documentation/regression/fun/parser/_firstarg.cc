#include "parser.ih"

RuleValue Parser::firstArg(RuleValue &rv)
{
    return RuleValue(new vector<RuleValue>(1, rv));
}
