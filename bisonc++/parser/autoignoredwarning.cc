#include "parser.ih"

void Parser::autoIgnoredWarning(char const *typeOrField) const
{
    wmsg << &d_rules.lastProduction() << ":\n"
            "\tany auto " << typeOrField << " for `" << d_rules.name() << 
                                                "' ignored at `$$.'" << endl;
}
