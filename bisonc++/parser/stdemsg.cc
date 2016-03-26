#include "parser.ih"

ostream &Parser::stdEmsg(AtDollar const &atd) const
{
    emsg.setLineNr(atd.lineNr());
    emsg << "rule " << &d_rules.lastProduction() << ": ";
    return emsg;
}
