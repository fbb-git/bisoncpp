#include "parser.ih"

void Parser::blkSTYPEW(string const &ruleType, Production const &prod)
{
    wmsg << '`' << &prod << 
            "': installed $$ = STYPE_{} action block" << endl;
    blkSTYPE(ruleType, prod);
}
