#include "parser.ih"

string Parser::dollarDollarPolymorphic(Block const &block, size_t pos) const
{
    string ret;

    if (callsMember(block, pos, "type"))
        return ret;

    switch (semTagDDP())
    {
        case UNTYPED:
            warnNoAuto("type");
        break;

        case TYPED:
            ret = ".get<" + d_rules.sType() + ">()";
        break;

        default:
        break;
    };

    return ret;
}

