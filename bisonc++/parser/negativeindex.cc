#include "parser.ih"

void Parser::negativeIndex(AtDollar const &atd) const
{
    if (not atd.id().empty())
    {
        emsg << &d_rules.lastProduction() << ": <" << atd.id() << 
            "> cannot be used with negative $-index (" << atd.text() << 
            ')' << endl;
        return;
    }

    if (d_negativeDollarIndices)
        return;

    wmsg.setLineNr(atd.lineNr());
    wmsg << &d_rules.lastProduction() << ": STYPE__ used for negative "
            "$-index (" << atd.text() << ')' << endl;
}
