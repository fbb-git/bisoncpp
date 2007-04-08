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

    switch (operation)
    {
        case '=':
            value = v2;
        break;
        case ADDA:
            value += v2;
        break;
        case SUBA:
            value -= v2;
        break;
        case MULA:
            value *= v2;
        break;
        case DIVA:
            div0(value, v2);
            value /= v2;
        break;
        case MODA:
            div0(value, v2);
            integral(value, v2);
            value %= v2;
        break;
        case ANDA:
            integral(value, v2);
            value &= v2;
        break;
        case XORA:
            integral(value, v2);
            value ^= v2;
        break;
        case ORA:
            integral(value, v2);
            value ^= v2;
        break;
        case RSHIFTA:
            integral(value, v2);
            value >>= v2;
        break;
        case LSHIFTA:
            integral(value, v2);
            value >>= v2;
        break;
    }
    return v1;
}






