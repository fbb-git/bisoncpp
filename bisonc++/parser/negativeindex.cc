#include "parser.ih"

void Parser::negativeIndex(AtDollar const &atd) const
{
    if (not atd.id().empty())
    {
        emsg << "rule " << &d_rules.lastProduction() << ":\n"
            "\t\t<" << atd.id() << 
            "> cannot be used for negative $-indices (" << atd.text() << 
            ')' << endl;
        return;
    }

    if (
        d_negativeDollarIndices 
        || 
        d_semType == SINGLE 
        || 
        d_rules.sType().empty()
    )
        return;

    wmsg.setLineNr(atd.lineNr());
    wmsg << "rule " << &d_rules.lastProduction() << ":\n"
            "\t\traw STYPE__ is used for negative $-indices (" << 
            atd.text() << ')' << endl;
}
