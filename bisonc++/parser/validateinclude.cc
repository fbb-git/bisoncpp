#include "parser.ih"

void Parser::validateInclude(string *target) 
{
    definePathname(target);
    setIncludeQuotes(target);
}

