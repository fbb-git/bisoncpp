#include "production.ih"

void Production::storeFilename(string const &filename)
{
    if 
    (
        find(s_fileName.begin(), s_fileName.end(), filename) 
        == s_fileName.end()
    )
        s_fileName.push_back(filename);
}
