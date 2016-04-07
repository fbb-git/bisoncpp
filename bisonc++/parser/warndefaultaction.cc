#include "parser.ih"

// static
void Parser::warnDefaultAction(Production const &prod) 
{
    wmsg << '`' << &prod << 
            "': installed $$ = STYPE__{} action block" << endl;
}
