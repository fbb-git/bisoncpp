#include "parser.ih"

string Parser::dollarTypedDollarPolymorphic(string const &typeSpec) const
{
    string ret;

    switch (semTagDTDP(typeSpec))
    {
        case DELTATYPED:
            warnAutoOverride("field", typeSpec);
            ret = ".get<" + typeSpec + ">()";
        break;

        case TYPED:
            ret = ".get<" + d_rules.sType() + ">()";
        // FALLING THROUGH

        default:
        break;
    }

    return ret;
}

