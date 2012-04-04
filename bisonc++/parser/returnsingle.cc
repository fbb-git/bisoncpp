#include "parser.ih"

void Parser::returnSingle(AtDollar const &atd) const
{
    if (atd.callsMember())
        return;

    semTag("", atd, &Parser::noID);
}

