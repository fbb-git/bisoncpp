#include "parser.ih"

string Parser::returnPolymorphic(AtDollar const &atd) const
{
    string ret = ".get";
 
    switch (semTag("tag", atd, &Parser::findTag))
    {
        case AUTO:          // use the %type specified semantic value
            ret +=  "<Tag__::" + 
                    (
                        atd.returnValue() ?
                            d_rules.sType() : d_rules.sType(atd.nr())
                    ) +
                    ">()";
        break;

        case EXPLICIT:
            ret += "<Tag__::" + atd.id() + ">()";
        break;

        case NONE:
            ret.clear();
        break;
    }

    return ret;
}



