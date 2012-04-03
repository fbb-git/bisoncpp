#include "parser.ih"

string Parser::dollarDollarUnion(Block const &block, size_t pos) const
{
    string ret;

cerr << "DOLLARDOLLARUNION\n";

    if (callsMember(block, pos, "field"))
        return ret;

    string const &autoField = d_rules.sType();

    if (autoField.empty())          // warn if there is no auto type
        warnNoAuto("field");
    else
        ret = "." + autoField;

    return ret;
}

