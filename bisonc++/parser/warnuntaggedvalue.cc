#include "parser.hh"

void Parser::warnUntaggedValue(AtDollar const &atd) const
{
    wmsg.setLineNr(atd.lineNr());
    wmsg << "rule " << &d_rules.lastProduction() << ":\n"
        "\t\tusing untagged semantic value `" << atd.text() << "'." << endl;
}
