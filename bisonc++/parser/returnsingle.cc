#include "parser.ih"

void Parser::returnSingle(AtDollar const &atd) const
{
    if (atd.callsMember())
        return;

    semTag("field", atd, &Parser::noID);
}

