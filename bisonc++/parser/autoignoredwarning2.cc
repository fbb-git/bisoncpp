#include "parser.ih"

void Parser::autoIgnoredWarning(int idx, char const *typeOrField) const
{
    if (not negativeIndexWarning(idx, typeOrField))
        wmsg << &d_rules.lastProduction() << ":\n"
            "\tignoring auto " << typeOrField << " for element " << idx <<
                                                                        endl;
}
