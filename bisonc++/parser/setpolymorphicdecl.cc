#include "parser.ih"

void Parser::setPolymorphicDecl()
{
    d_expect = "Polymorphic base class specifications";
    d_options.setPolymorphicDecl();
}

