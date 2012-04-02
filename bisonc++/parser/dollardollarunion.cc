#include "parser.ih"

string Parser::dollarDollarUnion(Block const &block, size_t pos) const
{
    string ret;

    if (callsMember(block, pos))
    {
        autoIgnoredWarning("field");
        return ret;
    }

    if (d_rules.sType().empty())    // warn if there is no default type
        noAutoWarning("field");
    else
        ret = "." + defaultType;

    return ret;
}

