#include "parser.ih"

string Parser::dollarTypedIndexPolymorphic(
                    size_t nElements, int idx, std::string const &autoTag, 
                    std::string const &tagName) const
{
    string ret;

    switch (semTagDTIP(nElements, autoTag, idx, tagName))
    {
        case TYPED:
            ret = ".get<" + autoTag + ">()";
        break;

        case DELTATYPED:
            ret = ".get<" + tagName + ">()";
        break;

        default:
        break;
    }

    return ret;
}


