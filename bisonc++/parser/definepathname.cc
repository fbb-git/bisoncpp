#include "parser.hh"

void Parser::definePathname(string *target)
{
    if (target->empty())            // assign only if not yet assigned
        *target = Options::undelimit(*target);
}
