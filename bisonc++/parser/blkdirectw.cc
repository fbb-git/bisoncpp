#include "parser.ih"

void Parser::blkDirectW(string const &ruleType, Production const &prod)
{
    wmsg << '`' << &prod << 
            "': installed $$ = $1 action block" << endl;

    blkDirect(ruleType, prod);
}
