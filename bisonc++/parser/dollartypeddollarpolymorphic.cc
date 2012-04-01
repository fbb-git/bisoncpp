#include "parser.ih"

string Parser::dollarTypedDollarPolymorphic(Block const &block, size_t pos,
                                            string const &typeSpec) const
{
    string ret;

    switch (polyType(typeSpec))
    {
        case DELTATYPED:
            ret = ".get<" + typeSpec + ">()";
        break;

        case TYPED:
            ret = ".get<" + defaultType + ">()";
        break;

        default:
        break;
    };

    return ret;
}

