#include "_rulevalue.hh"

RuleValue &RuleValue::operator=(RuleValue const &other)
{
    if (this != &other)
    {
        destroy();
        copy(other);
    }
    return *this;
}

