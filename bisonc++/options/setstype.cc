#include "options.ih"

void Options::setStype()
{
    if (not isFirstStypeDefinition())
        return;

    if (d_matched->find(';') != string::npos)
        emsg << "`;' in %stype type-definition `" << *d_matched << 
                '\'' << endl;
    else
        d_stackDecl = "typedef " + *d_matched + " STYPE__;\n";
}
