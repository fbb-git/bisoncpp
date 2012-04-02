#include "parser.ih"

string Parser::dollarIndexUnion(Block const &block, size_t pos, 
                                size_t nRuleElments, int idx, 
                                string const &elementType) const 
{
    string ret;

    if (callsMember(block, pos))
    {
        autoIgnoredWarning(idx, "field");
        return ret;
    }

    switch (semTagDIU(nRuleElements, idx, elementType))
    {
        case TYPEIGNORED:
            autoIgnoredWarning(idx, "field");
        break;

        default:
        case UNTYPED:
            noAutoWarning(idx, "field");
        break;

        case TYPED:
            ret = "." + elementType;
        break;
    }

    return ret;
}


