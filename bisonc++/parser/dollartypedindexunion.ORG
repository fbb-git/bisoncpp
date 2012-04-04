#include "parser.ih"

string Parser::dollarTypedIndexUnion(
        size_t nElements, int idx, string const &autoField, 
        string const &unionField) const
{
    string ret;

    switch (semTagDTIU(nElements, autoField, idx, unionField))
    {
        default:
        break;

        case TYPED:
            ret = "." + autoField;
        break;

        case DELTATYPED:
            warnAutoOverride("field", unionField);
            ret = "." + unionField;
        break;
    }

    return ret;
}


