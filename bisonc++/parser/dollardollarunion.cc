#include "parser.ih"

string Parser::dollarDollarUnion(Block const &block, size_t pos) const
{
    string ret;

    if (callsMember(block, pos))
    {
        autoIgnoredWarning("field");
        return ret;
    }

    string const &autoField = d_rules.sType();

    if (autoField.empty())          // warn if there is no auto type
        noAutoWarning("field");
    else
        ret = "." + autoField;

    return ret;
}

