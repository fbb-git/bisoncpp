#include "_rulevalue.ih"

void RuleValue::copy(RuleValue const &other)
{
    d_tag = other.d_tag;
    if (d_tag != ARG_VECTOR)
        d_value = other.d_value;
    else
        d_value.args = new std::vector<RuleValue>(*other.d_value.args);
}

