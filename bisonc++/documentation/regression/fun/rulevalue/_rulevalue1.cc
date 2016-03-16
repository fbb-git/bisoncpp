#include "_rulevalue.ih"

RuleValue::RuleValue()
:
    d_tag(ERROR)
{}

RuleValue::RuleValue(char c)
:
    d_tag(CHAR)
{
    d_value.c = c;
}

RuleValue::RuleValue(int i)
:
    d_tag(INT)
{
    d_value.i = i;
}

RuleValue::RuleValue(unsigned s)
:
    d_tag(VARIABLE)
{
    d_value.s = s;
}

RuleValue::RuleValue(double d)
:
    d_tag(DOUBLE)
{
    d_value.d = d;
}

RuleValue::RuleValue(Function const &funRef)
:
    d_tag(FUNCTION)
{
    d_value.f = &funRef;
}


RuleValue::RuleValue(Args *args)
:
    d_tag(ARG_VECTOR)
{
    d_value.args = args;
}
