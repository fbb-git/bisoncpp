#include "parser.ih"

void Parser::warnNoAuto(int idx, char const *typeOrField) const
{
    wmsg << &d_rules.lastProduction() << ":\n"
            "\tno auto " << typeOrField << " for element " << idx << endl;
}
