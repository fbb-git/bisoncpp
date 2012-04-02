#include "parser.ih"

void Parser::autoOverrideWarning(char const *typeOrField, 
                                string const &override) const
{
    wmsg << &d_rules.lastProduction() << ":\n"
            "\tforcing `%type <" << override << ">'" << endl;
}
