#include "options.ih"

void Options::setSkeletonDirectory(string const &name)
{
    if (d_skeletonDirectory.size())
        cerr << "%skeleton-directory (-S) specified multiple times\n";
    else
        setPath(&d_skeletonDirectory, name);
}
