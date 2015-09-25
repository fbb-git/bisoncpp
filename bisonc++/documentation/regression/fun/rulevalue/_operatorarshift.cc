#include "_rulevalue.ih"

//    Here, the parser makes sure that we're already using integral values

RuleValue &RuleValue::operator>>=(RuleValue const &other)
{
    d_value.i = asInt() >> other.asInt();
    d_tag = INT;

    return *this;
}
