#include "options.ih"

void Options::addIncludeQuotes(string &target) 
{
    if (target.find_first_of("<\"") != 0)
        target.insert(0, 1, '"') += '"';
}

