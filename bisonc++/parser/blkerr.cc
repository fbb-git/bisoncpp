#include "parser.ih"

void Parser::blkErr(string const &ruleType, Production const &prod)
{
    emsg << '`' << &prod << "':  type clash ($$: " << 
        nameOf(ruleType) << ", $1: " << nameOf(prod[0].sType()) <<
        ") prevents auto-appending default action `$$ = $1'" << endl;
}

