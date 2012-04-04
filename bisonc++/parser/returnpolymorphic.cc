#include "parser.ih"

string Parser::returnPolymorphic(AtDollar const &atd) const
{
    string ret;

    if (callsMember("tag", atd))
        return ret;

    switch (semTag("tag", atd, &Parser::findTag))
    {
        case AUTO:          // use the %type specified semantic value
            ret = ".get<" + d_rules.sType() + ">()";
        break;

        case EXPLICIT:
            ret = ".get<" + atd.id() + ">()";
        break;

        case NONE:
        break;
    }

    return ret;
}

