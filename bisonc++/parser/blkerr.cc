#include "parser.ih"

void Parser::blkErr(string const &ruleType, Production const &prod)
{
    emsg << '`' << &prod << "':  type conflict ($$: " << 
        nameOf(ruleType) << ", $1: " << nameOf(prod[0].sType()) <<
        "): cannot auto-append default action `$$ = $1'" << endl;
}

