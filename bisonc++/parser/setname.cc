#include "parser.ih"

void Parser::setName(string *target, char const *extension) 
{
    *target = 
        (d_genericFilename.empty() ? d_className : d_genericFilename) + 
        extension;
}
