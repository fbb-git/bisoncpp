#include "parser.ih"

string Parser::returnUnion(AtDollar const &atd) const
{
    string ret;

    switch (semTag("field", atd, &Parser::idOK))
    {
        case NONE:
        break;

        case AUTO:
            ret = "." + d_rules.sType();
        break;

        case EXPLICIT:
            ret = "." + atd.id();
        break;
    }

    return ret;
}

