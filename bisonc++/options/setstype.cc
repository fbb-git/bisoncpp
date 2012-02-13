#include "options.ih"

void Options::setStype()
{
    if (d_stackDecl.size())
        emsg << "%union or %stype multiply specified" << endl;
    else if (d_matched->find(';') != string::npos)
        emsg << "`;' in %stype type-definition `" << *d_matched << 
                '\'' << endl;
    else
        d_stackDecl = "typedef " + *d_matched + " STYPE__;\n";
}
