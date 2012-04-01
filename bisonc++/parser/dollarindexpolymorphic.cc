#include "parser.ih"

string Parser::dollarIndexPolymorphic(
        int idx,
        string const &idxType,
        size_t nElements

                ) const
{

    string ret;

    switch (polyType(idxType, "", idx, nElements))
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

