#include "parser.ih"

string Parser::dollarIndexUnion(Block const &block, size_t pos, 
                                size_t nRuleElements, int idx, 
                                string const &elementType) const 
{
    string ret;

//    if (callsMember(block, pos, "field", idx))
        return ret;

cerr << "NO MEMBER CALL\n";

    switch (semTagDIU(nRuleElements, idx, elementType))
    {
        case TYPEIGNORED:
//            warnAutoIgnored("field", idx);
        break;

        default:
        case UNTYPED:
            warnNoAuto(idx, "field");
        break;

        case TYPED:
            ret = "." + elementType;
        break;
    }

    return ret;
}


