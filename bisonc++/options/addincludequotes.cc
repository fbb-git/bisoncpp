#include "options.ih"

void Options::addIncludeQuotes(string &target) 
{
    if 
    (
        target.size()                           // target specified
        &&
        target.find_first_of("<\"") != 0        // but no initial quotes
    )
        target.insert(0, 1, '"') += '"';
}

