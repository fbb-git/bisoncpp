#include "parser.ih"

// copy the union declaration into ostringstream `union_decl' as the
// definition of LSTYPE.

void Parser::setUnionDecl()
{
    if (d_stackDecl.size())
        lineMsg() << "%union or %stype multiply declared" << err;

    d_stackDecl = "union STYPE\n";  // USED TO BE struct, BUT union IS
                                    // INTENDED

    d_unionDeclared = true;         // if a %union is used, then the rules
                                    // MUST have an associated return type if
                                    // a plain $$ is used. Also, a union must
                                    // be available if a $<field> construction
                                    // is used.

    if (!d_scanner.block(&d_block))
        lineMsg() << "`%union { ... }' expected" << err;
    else
        (d_stackDecl += d_block) += ";\n";

    if (d_scanner.lex() != ';')                     // trailing ; is ok
        d_scanner.unget();                          // but none is ok too.
}
