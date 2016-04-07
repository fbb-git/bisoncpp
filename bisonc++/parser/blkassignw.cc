#include "parser.ih"

void Parser::blkAssignW(string const &ruleType, Production const &prod)
{
    wmsg << '`' << &prod << 
            "': installed $$ = $1.get<type>() action block" << endl;

    blkAssign(ruleType, prod);
}
