#include "parser.ih"

void Parser::addIncludeQuotes(string *target) 
{
    if (target->find_first_of("<\"") == 0)
        return;

    target->insert(0, 1, '"') += "\"";
}

