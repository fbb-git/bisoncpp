#include "options.ih"

// copy the union declaration into ostringstream `union_decl' as the
// definition of LSTYPE.

void Options::setUnionDecl(std::string const &block)
{
    if (d_stackDecl.size())
        emsg << "%union or %stype multiply specified" << endl;
    else
        d_stackDecl = "union STYPE__\n" + block + ";\n";
}

