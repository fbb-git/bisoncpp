#include "_rulevalue.ih"

char RuleValue::asChar() const
{
    switch(d_tag)
    {
        case CHAR:
        return d_value.c;

        case INT:
        return static_cast<char>(d_value.i);

        default:
        return static_cast<char>(d_value.d);
    }
}

int RuleValue::asInt() const
{
    switch(d_tag)
    {
        case CHAR:
        return d_value.c;

        case INT:
        return d_value.i;

        default:
        return static_cast<int>(d_value.d);
    }
}

double RuleValue::asDouble() const
{
    switch(d_tag)
    {
        case CHAR:
        return d_value.c;

        case INT:
        return d_value.i;

        default:
        return d_value.d;
    }
}

RuleValue::Function const &RuleValue::fun() const
{
    return *d_value.f;
}

