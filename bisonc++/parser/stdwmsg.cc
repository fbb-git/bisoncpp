#include "parser.ih"

ostream &Parser::stdWmsg(AtDollar const &atd) const
{
    wmsg.setLineNr(atd.lineNr());
    wmsg << "rule " << &d_rules.lastProduction() << ": ";
    return wmsg;
}
