#include "parser.ih"

RuleValue &Parser::lvalue(RuleValue &e)
{
    return e.tag() == RuleValue::VARIABLE ?
                d_value[e.varIdx()]
            :
                e;
}

RuleValue const &Parser::rvalue(RuleValue const &e) const
{
    return e.tag() == RuleValue::VARIABLE ?
                d_value[e.varIdx()]
            :
                e;
}

