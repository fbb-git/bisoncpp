#include "parser.ih"

void Parser::autoIgnoredWarning(int idx, char const *typeOrField) const
{
    wmsg << &d_rules.lastProduction() << ":\n"
            "\tignoring any auto " << typeOrField << " for element " << idx <<
                                                                        endl;
}
