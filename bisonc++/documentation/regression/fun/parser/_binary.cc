#include "parser.ih"

RuleValue Parser::binary(RuleValue v1, int operation, RuleValue const &v2)
{
    error(
        v1.tag() == RuleValue::FUNCTION ||v2.tag() == RuleValue::FUNCTION,
        "Function names have no values. Forgot arguments?"
    );

    RuleValue v1x{ rvalue(v1) };
    RuleValue v2x{ rvalue(v2) };

    switch (operation)
    {
        case '+':
            v1x += v2x;
        break;

        case '-':
            v1x -= v2x;
        break;

        case '*':
            v1x *= v2x;
        break;

        case '/':
            div0(v1x, v2x);
            v1x /= v2x;
        break;

        case '%':
            div0(v1x, v2x);
            integral(v1x, v2x);
            v1x %= v2x;
        break;

        case '&':
            integral(v1x, v2x);
            v1x &= v2x;
        break;

        case '^':
            v1x ^= v2x;
        break;

        case '|':
            v1x |= v2x;
        break;

        case RIGHTSHIFT:
            v1x >>= v2x;
        break;

        case LEFTSHIFT:
            v1x <<= v2x;
        break;
    }

    return v1x;
}






