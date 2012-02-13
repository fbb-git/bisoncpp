#include "parser.ih"

void Parser::setUnionDecl()
{
    d_options.setUnionDecl(d_scanner.block().str());
    d_unionDeclared = true;     // if a %union is used, then the rules
                                // MUST have an associated return type if
}                               // a plain $$ is used. Also, a union must
                                // be available if a $<field> construction
                                // is used.

