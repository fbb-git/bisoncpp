#include "parser.ih"

string Parser::dollarTypedDollarUnion(std::string const &typeSpec) const
{
    string const *typePtr = &d_rules.sType();    // get the default type

                            // warn if the rule has no associated type
    if (typeSpec.length())
    {
        typePtr = &typeSpec;
        if (not defaultType->length())
            noDefaultTypeWarning();
    }

    string ret;

    if (typePtr->length())      // use an explicit type if available
        ret = "." + *typePtr;

    return ret;
}

