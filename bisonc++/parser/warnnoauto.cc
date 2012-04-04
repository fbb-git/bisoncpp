#include "parser.ih"

void Parser::warnNoAuto(char const *typeOrField, AtDollar const &atd) const
{
    wmsg.setLineNr(atd.lineNr());
    wmsg << &d_rules.lastProduction() << ":\n"
            "\tno auto " << typeOrField << " for `" << d_rules.name() << "'"
            " (" << atd.text() << ')' << endl;
}
