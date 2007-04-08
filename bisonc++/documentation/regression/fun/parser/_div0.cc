#include "parser.ih"

void Parser::div0(RuleValue const &vl, RuleValue const &vr)
{
    error(
        abs(vl.asDouble()) > 1e100 * abs(vr.asDouble()),
        "Number too large"
    );
}
