#include "options.ih"

// copy the union declaration into ostringstream `union_decl' as the
// definition of LSTYPE.

void Options::setUnionDecl(std::string const &block)
{
    if (d_stackDecl.size())
        emsg << "%union or %stype multiply specified" << endl;
    else
    {
        d_stackDecl = "union STYPE__\n" + block + ";\n";

        d_unionDeclared = true;     // if a %union is used, then the rules
    }                               // MUST have an associated return type if
}                                   // a plain $$ is used. Also, a union must
                                    // be available if a $<field> construction
                                    // is used.

