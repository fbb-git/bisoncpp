#include "_rulevalue.ih"

RuleValue &RuleValue::operator=(RuleValue const &other)
{
    if (this != &other)
    {
        destroy();
        copy(other);
    }
    return *this;
}

