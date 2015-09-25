#include "options.ih"

void Options::setLtype()
{
    if (d_locationDecl.size())
        emsg << "%location-struct or %ltype multiply declared" << endl;
    else if (d_matched->find(';') != string::npos)
        emsg << "`;' in %ltype type-definition `" << *d_matched << 
                '\'' << endl;
    else
        d_locationDecl = "typedef " + *d_matched += " LTYPE__;\n";
}



