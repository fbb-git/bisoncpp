#include "parser.ih"

void Parser::validateInclude(string *target) 
{
    definePathname(target);

    if (target->find_first_of("<\"") == 0)
        return;

    *target = "\"" + *target + "\"";
}

