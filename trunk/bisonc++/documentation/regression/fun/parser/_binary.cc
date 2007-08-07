#include "parser.ih"

RuleValue Parser::binary(RuleValue v1, int operation, RuleValue const &v2)
{
    error(
        v1.tag() == RuleValue::FUNCTION ||v2.tag() == RuleValue::FUNCTION,
        "Function names have no values. Forgot arguments?"
    );

    switch (operation)
    {
        case '+':
            v1 += v2;
        break;

        case '-':
            v1 -= v2;
        break;

        case '*':
            v1 *= v2;
        break;

        case '/':
            div0(v1, v2);
            v1 /= v2;
        break;

        case '%':
            div0(v1, v2);
            integral(v1, v2);
            v1 %= v2;
        break;

        case '&':
            integral(v1, v2);
            v1 &= v2;
        break;

        case '^':
            v1 ^= v2;
        break;

        case '|':
            v1 |= v2;
        break;

        case RIGHTSHIFT:
            v1 >>= v2;
        break;

        case LEFTSHIFT:
            v1 <<= v2;
        break;
    }

    return v1;
}






