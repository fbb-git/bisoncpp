#include "parser.ih"

void Parser::integral(RuleValue const &v1)
{
    error
    (
        v1.tag() != RuleValue::CHAR && v1.tag() != RuleValue::INT,
        "Non-integral operand on integral operator"
    );
}

void Parser::integral(RuleValue const &v1, RuleValue const &v2)
{
    integral(v1);
    integral(v2);
}





