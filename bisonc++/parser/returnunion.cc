#include "parser.ih"

string Parser::returnUnion(Block const &block, AtDollar const &atd) const
{
    string ret;

    if (callsMember("field", atd))
        return ret;

    string const &autoField = d_rules.sType();

    if (autoField.empty())          // warn if there is no auto type
        warnNoAuto("field");
    else
        ret = "." + autoField;

    return ret;
}

