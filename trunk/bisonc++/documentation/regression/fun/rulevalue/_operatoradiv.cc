#include "_rulevalue.ih"

RuleValue &RuleValue::operator/=(RuleValue const &other)
{
    if (d_tag == DOUBLE || other.d_tag == DOUBLE)
    {
        d_value.d = asDouble() / other.asDouble();
        d_tag = DOUBLE;
    }
    else
    {
        d_value.i = asInt() / other.asInt();
        d_tag = INT;
    }
    return *this;
}
