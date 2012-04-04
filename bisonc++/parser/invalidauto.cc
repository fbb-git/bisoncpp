#include "parser.ih"

void Parser::errInvalidAuto(AtDollar const &atd) const
{
    emsg.setLineNr(atd.lineNr());

    emsg << &d_rules.lastProduction() << 
                ": unknown %polymorphic tag for "
                "%type <" << d_rules.sType() << "> " << d_rules.name() <<
                " (" << atd.text() << ')' << endl;
}
