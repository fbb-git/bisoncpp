#include "parser.ih"

RuleValue &Parser::assign(RuleValue &v1, int operation, RuleValue const &v2)
{
    if (d_error)
        return v1;

    error(v1.tag() != RuleValue::VARIABLE, "Non-lvalue in assignment");

    error(
        v2.tag() == RuleValue::FUNCTION,
        "Function names have no values. Forgot arguments?"
    );

    RuleValue &value = lvalue(v1);
    RuleValue const &rv2 = rvalue(v2);

    switch (operation)
    {
        case '=':
            value = rv2;
        break;
        case ADDA:
            value += rv2;
        break;
        case SUBA:
            value -= rv2;
        break;
        case MULA:
            value *= rv2;
        break;
        case DIVA:
            div0(value, rv2);
            value /= rv2;
        break;
        case MODA:
            div0(value, rv2);
            integral(value, rv2);
            value %= rv2;
        break;
        case ANDA:
            integral(value, rv2);
            value &= rv2;
        break;
        case XORA:
            integral(value, rv2);
            value ^= rv2;
        break;
        case ORA:
            integral(value, rv2);
            value ^= rv2;
        break;
        case RSHIFTA:
            integral(value, rv2);
            value >>= rv2;
        break;
        case LSHIFTA:
            integral(value, rv2);
            value >>= rv2;
        break;
    }
    return v1;
}






