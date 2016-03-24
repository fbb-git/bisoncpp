#include "scanner.ih"

    // called when matching $$ = [^$]: a direct assignment to $$ from
    // something untagged. 
void Scanner::warnAssign() 
{
    if (d_matched.back() != '$' && d_warnAssign)
        wmsg << "direct assignment of an untagged value to $$. "
                                            "Maybe use $$(...)?" << endl;

    accept(2);

    d_block.dollar(lineNr(), d_matched, false);
}
