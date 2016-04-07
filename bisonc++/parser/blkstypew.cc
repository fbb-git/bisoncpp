#include "parser.ih"

void Parser::blkSTYPEW(string const &ruleType, Production const &prod)
{
    wmsg << '`' << &prod << 
            "': installed $$ = STYPE__{} action block" << endl;
    blkSTYPE(ruleType, prod);
}
