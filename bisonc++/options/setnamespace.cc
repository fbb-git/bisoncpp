#include "options.ih"

void Options::setNameSpace(string const &name)
{
    if (d_nameSpace.size())
        cerr << "%namespace multiply specified\n";
    else
        d_nameSpace = undelimit(name);
}
