#include "parser.ih"

void Parser::warnAutoOverride(char const *typeOrField, 
                                string const &override) const
{
    wmsg << &d_rules.lastProduction() << ": forcing `%type <" << override << 
            ">'" << endl;
}
