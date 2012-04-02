#include "parser.ih"

void Parser::autoIgnoredWarning(char const *typeOrField) const
{
    wmsg << &d_rules.lastProduction() << ":\n"
            "\tignoring auto " << typeOrField << " for `" << d_rules.name() << 
                                                '\'' << endl;
}



