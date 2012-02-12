#include "option.ih"

void Options::setLtype(std::string const &matched)
{
    if (d_locationDecl.size())
        emsg << "%location-struct or %ltype multiply declared" << endl;
    else if (matched.find(';') != string::npos)
        emsg << "`;' in %ltype type-definition `" << matched << '\'' << endl;
    else
    { 
        d_locationDecl = "typedef " + matched += " LTYPE__;\n";
        d_lspNeeded = true;
    }
}



