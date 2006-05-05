#include "parser.ih"

void Parser::setIncludeQuotes(string *target) 
{
    if (target->find_first_of("<\"") == 0)
        return;

    *target = "\"" + *target + "\"";
}

