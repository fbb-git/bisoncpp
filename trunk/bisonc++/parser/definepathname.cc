#include "parser.ih"

void Parser::definePathname(string *target, int type)
{
    if (!target->size())            // assign only if not yet assigned
    {
        if (type != 0)
            d_scanner.undelimit(type == PSTRING);
        *target = String::unescape(d_scanner.YYText());
    }
}
