#include "parser.ih"

// copy the union declaration into ostringstream `union_decl' as the
// definition of LSTYPE.

void Parser::setUnionDecl()
{
    if (d_stackDecl.size())
        lineMsg() << "%union or %stype multiply specified" << err;

    (d_stackDecl = "union STYPE__\n" + d_scanner.block()) += ";\n";

    d_unionDeclared = true;         // if a %union is used, then the rules
                                    // MUST have an associated return type if
                                    // a plain $$ is used. Also, a union must
                                    // be available if a $<field> construction
                                    // is used.
}
