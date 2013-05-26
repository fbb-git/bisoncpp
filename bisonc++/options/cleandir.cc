#include "options.ih"

void Options::cleanDir(string &dir, bool append)
{
    dir = undelimit(dir);

    if (append && *dir.rbegin() != '/')
        dir += '/';
}
