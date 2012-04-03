#include "parser.ih"

void Parser::warnNoAuto(char const *typeOrField) const
{
    wmsg << &d_rules.lastProduction() << ":\n"
            "\tno auto " << typeOrField << " for `" << d_rules.name() << "'"
            " ($$)" << endl;
}
