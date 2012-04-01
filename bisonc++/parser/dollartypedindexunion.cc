#include "parser.ih"

string Parser::dollarTypedIndexUnion(
        int idx,
        string const &idxType,
        size_t nElements,
        string const &specType,

                ) const
{

    string ret;

    switch (unionType(idxType, specType, idx, nElements))
    {
        default:
        break;

        case TYPED:
            ret = "." + idxType;
        break;

        case DELTATYPED:
            ret = "." + specType;
        break;
    }

    return ret;
}


