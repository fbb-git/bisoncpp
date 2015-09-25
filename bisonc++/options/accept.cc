#include "options.ih"

std::string const &Options::accept(PathType pathType, char const *declTxt)
{
    if (pathType == FILENAME && d_matched->find('/') != string::npos)
        emsg << '`' << declTxt << "' directive: no path names" << endl;

    return *d_matched;
}
