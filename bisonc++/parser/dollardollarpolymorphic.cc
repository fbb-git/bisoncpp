#include "parser.ih"

string Parser::dollarDollarPolymorphic(Block const &block, size_t pos) const
{
    string ret;

    if (callsMember(block, pos))
        return ret;

    switch (polyType())
    {
        case TYPED:
            ret = ".get<" + defaultType + ">()";
        break;

        default:
        break;
    };

    return ret;
}

