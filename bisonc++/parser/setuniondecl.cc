#include "parser.ih"

void Parser::setUnionDecl()
{
    d_options.setUnionDecl(d_scanner.block().str());
    d_semType = UNION;          // if a %union is used, then the rules
    d_atDollar = &s_union;      // MUST have an associated return type if
}                               // a plain $$ is used. Also, a union must
                                // be available if a $<field> construction
                                // is used. (unless default-actions std is 
                                // was specified

