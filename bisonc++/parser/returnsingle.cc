#include "parser.hh"

void Parser::returnSingle(AtDollar const &atd) const
{
    if (atd.callsMember())
        return;

    semTag("field", atd, &Parser::noID);
}

