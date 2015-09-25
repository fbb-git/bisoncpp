#include "options.ih"

// copy the union declaration into ostringstream `union_decl' as the
// definition of LSTYPE.

void Options::setUnionDecl(std::string const &block)
{
    if (isFirstStypeDefinition())
        d_stackDecl = "union STYPE__\n" + block + ";\n";
}

