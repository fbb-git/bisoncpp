#include "parser.ih"

bool Parser::existingTag(AtDollar const &atd) const
{
    if (d_polymorphic.find(atd.tag()) != d_polymorphic.end())
        return true;

    stdEmsg(atd) << "tag `" << atd.tag() << "' not defined" << endl;
    return false;
}
