#include "parser.ih"

RuleValue Parser::unary(int operation, RuleValue const &e)
{
    if (d_error)
        return e;

    error(e.tag() == RuleValue::FUNCTION, 
        "Function names have no values. Forgot argument(s)?");

    RuleValue value = rvalue(e);

    switch (operation)
    {
        case RuleValue::CHAR:
        return RuleValue(value.asChar());

        case RuleValue::INT:
        return RuleValue(value.asInt());

        case RuleValue::DOUBLE:
        return RuleValue(value.asDouble());

        case '-':
        return RuleValue(-value);

        case '~':
            integral(value);
        return RuleValue(~value);

        default:
            error(true, "Illegal operand for unary operator");
        break;
    }

    return value;           // not reached
}


