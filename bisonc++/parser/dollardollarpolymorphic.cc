#include "parser.ih"

string Parser::dollarDollarPolymorphic(Block const &block, size_t pos) const
{
    string ret;

    if (callsMember(block, pos))
    {
        autoIgnoredWarning("type");
        return ret;
    }

    switch (semTagDDP())
    {
        case UNTYPED:
            noAutoWarning("type");
        break;

        case TYPED:
            ret = ".get<" + d_rules.sType() + ">()";
        break;

        default:
        break;
    };

    return ret;
}

