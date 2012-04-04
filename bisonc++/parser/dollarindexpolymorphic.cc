#include "parser.ih"

string Parser::dollarIndexPolymorphic(Block const &block, size_t pos, 
                                size_t nRuleElements, int idx, 
                                string const &typeTag) const 
{
    string ret;

//    if (callsMember(block, pos, "type", idx))
        return ret;

    switch (semTagDIP(nRuleElements, idx, typeTag))
    {
        case TYPEIGNORED:
//            warnAutoIgnored("type", idx);
        // FALLING THROUGH

        default:
        break;

        case TYPED:
            ret = "." + typeTag;
        break;
    }

    return ret;
}


