#include "parser.hh"

void Parser::setPolymorphicDecl()
{
    d_expect = "Polymorphic base class specifications";
    d_options.setPolymorphicDecl();
    d_semType = POLYMORPHIC;
}

