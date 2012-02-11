#include "options.ih"

void Options::setClassName(string const &name)
{
    if (d_className.size())
        cerr << "%class-name (--class-name) multiply specified\n";
    else
        d_className = undelimit(name);
}
