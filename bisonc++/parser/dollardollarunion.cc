#include "parser.ih"

string Parser::dollarDollarUnion() const
{
    string ret;

    if (d_rules.sType().empty())    // warn if there is no default type
        noDefaultTypeWarning();
    else
        ret = "." + defaultType;

    return ret;
}

