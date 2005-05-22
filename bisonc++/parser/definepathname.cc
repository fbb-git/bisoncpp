#include "parser.ih"

void Parser::definePathname(string *sp)
{
                                // retrieve the next string from the
                                // specification file 
    string path = d_scanner.nextString();

    if (!sp->size())            // assign only if not yet assigned
        *sp = path;
}
