#include "parser.ih"

string Parser::dollarIndexPolymorphic(Block const &block, size_t pos, 
                                size_t nRuleElements, int idx, 
                                string const &typeTag) const 
{
    string ret;

    if (callsMember(block, pos))
    {
        autoIgnoredWarning(idx, "type");
        return ret;
    }

    switch (semTagDIP(nRuleElements, idx, typeTag))
    {
        case TYPEIGNORED:
            autoIgnoredWarning(idx, "type");
        // FALLING THROUGH

        default:
        break;

        case TYPED:
            ret = "." + typeTag;
        break;
    }

    return ret;
}


