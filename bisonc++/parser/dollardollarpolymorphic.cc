#include "parser.ih"

string Parser::dollarDollarPolymorphic(Block const &block, size_t pos) const
{
    string ret;

    switch (polyType())
    {
        case TYPED:
            if (not callsMember(block, pos))
                ret = ".get<" + d_rules.sType() + ">()";
            else
                wmsg << "$$. ignores auto-type for " << d_rules.name() << 
                        endl;
        break;

        default:
        break;
    };

    return ret;
}

