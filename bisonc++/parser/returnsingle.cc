#include "parser.ih"

    // $$               no deref, no members: OK
    // $-?NR 

    // ($$)             deref: ignore the ()s
    // ($NR) 

    // $$.              members
    // $$-> 
    // $NR. 
    // $NR->

void Parser::returnSingle(AtDollar const &atd) const
{
    if (atd.callsMember())
        return;

    semTag("field", atd, &Parser::noID);
}

