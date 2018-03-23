#include "parser.ih"

// static
void Parser::warnDefaultAction(Production const &prod) 
{
    wmsg << '`' << &prod << 
            "': installed $$ = STYPE_{} action block" << endl;
}
