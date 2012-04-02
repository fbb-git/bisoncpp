#include "parser.ih"

void Parser::noAutoWarning(int idx, char const *typeOrField) const
{
    wmsg << &d_rules.lastProduction() << ":\n"
            "\tno auto " << typeOrField << " for element " << idx) << endl;
}
