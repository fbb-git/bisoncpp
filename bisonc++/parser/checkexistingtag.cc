#include "parser.ih"

bool Parser::checkExistingTag(AtDollar const &atd) const
{
    if (d_polymorphic.find(atd.tag()) != d_polymorphic.end())
        return true;

    emsg.setLineNr(atd.lineNr());
    emsg << "tag `" << atd.tag() << "' not defined" << endl;
    return false;
}
