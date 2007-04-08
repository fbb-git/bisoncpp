#include "_rulevalue.ih"

RuleValue RuleValue::operator-() const
{
    switch (d_tag) 
    {
        case CHAR:
        return RuleValue(-asChar());

        case INT:
        return RuleValue(-asInt());

        default:
        return RuleValue(-asDouble());
    }
}
