#include "parser.ih"

void Parser::noAutoWarning(char const *typeOrField) const
{
    wmsg << &d_rules.lastProduction() << ":\n"
            "\tno auto " << typeOrField << " for `" << d_rules.name() << "'"
            " ($$)" << endl;
}
