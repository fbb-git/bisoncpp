#include "parser.ih"

void Parser::setPolymorphicDecl()
{
    d_expect = "Polymorphic base class specifications";
    d_options.setPolymorphicDecl();
    d_semType = POLYMORPHIC;
    d_atDollar = &s_polymorphic;
}

