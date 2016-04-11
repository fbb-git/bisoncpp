#include "parser.ih"

ostream &Parser::stdWmsg(AtDollar const &atd) const
{
    wmsg.setLineNr(atd.lineNr());
    wmsg << "rule " << &d_rules.lastProduction() << ": ";
    wmsg.setLineNr(atd.lineNr());
    return wmsg;
}
