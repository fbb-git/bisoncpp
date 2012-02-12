#include "options.ih"

void Options::setStype(string const &spec)
{
    if (d_stackDecl.size())
        emsg << "%union or %stype multiply specified" << endl;
    else if (spec.find(';') != string::npos)
        emsg << "`;' in %stype type-definition `" << txt << '\'' << endl;
    else
        d_stackDecl = "typedef " += txt + " STYPE__;\n";
}
