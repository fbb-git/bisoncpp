#include "_rulevalue.ih"

RuleValue::Function::Function(double (*ptr)(double), Type t)
:
    d_type(t),
    d_arity(1)
{
    d_ptr.unary = ptr;
}

RuleValue::Function::Function(double (*ptr)(double, double))
:
    d_type(DOUBLE_IN_DOUBLE_OUT),
    d_arity(2)
{
    d_ptr.binary = ptr;
}

