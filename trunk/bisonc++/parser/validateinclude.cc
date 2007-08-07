#include "parser.ih"

void Parser::validateInclude(string *target) 
{
    definePathname(target, 0);
    addIncludeQuotes(target);
}

