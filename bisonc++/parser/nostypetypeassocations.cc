#include "parser.ih"

void Parser::noSTYPEtypeAssociations() const
{
    emsg << &d_rules.lastProduction() << ":\n"
            "\ttype associations only available for %union and "
            "%polymorphic" << endl;
}
