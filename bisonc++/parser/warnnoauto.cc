#include "parser.ih"

void Parser::warnNoAuto(char const *label, AtDollar const &atd) const
{
    wmsg.setLineNr(atd.lineNr());
    wmsg << &d_rules.lastProduction() << ": using " << label << " `" << 
            label << " for `" << d_rules.name() << "'"
            " (" << atd.text() << ')' << endl;
}
