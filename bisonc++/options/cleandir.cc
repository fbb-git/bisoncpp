#include "options.ih"

void Options::cleanDir(string &dir)
{
    dir = undelimit(dir);

    if (*dir.rbegin() != '/')
        dir += '/';
}
