#include "parser.ih"

string Parser::dollarIndexUnion() const
{
    string ret;

    switch (unionType(idxType, "", idx, nElements))
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


