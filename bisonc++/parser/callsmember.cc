#include "parser.ih"

bool Parser::callsMember(char const *typeOrField, AtDollar const &atd) const
{
    if (not atd.callsMember())
        return false;

    warnAutoIgnored(typeOrField, atd);
    return true;
}

