#include "options.ih"

// copy the location declaration into `d_locationDecl' as the
// definition of LSTYPE.

void Options::setLocationDecl(std::string const &block)
{
    if (!d_locationDecl.empty())
        emsg << "%location-struct or %ltype multiply specified" << endl;
    else
    {
        d_locationDecl = "struct LTYPE__\n" + block += ";\n";
        d_lspNeeded = true;
    }
}
