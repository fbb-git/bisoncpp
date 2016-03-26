#include "parser.ih"

string Parser::returnUnion(AtDollar const &atd) const
{
    string ret;

    switch (semTag("field", atd, &Parser::idOK))
    {
        case NONE:
        break;

        case AUTO:
            ret =   "." + 
                    (
                        atd.dollarDollar() ?
                            d_rules.sType() : d_rules.sType(atd.nr())
                    );
        break;

        case EXPLICIT:
            ret = "." + atd.tag();
        break;
    }

    return ret;
}

