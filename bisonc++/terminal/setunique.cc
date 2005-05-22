#include "terminal.ih"

bool Terminal::setUnique(unsigned value) 
{
    if (s_valueSet.count(value))
        return false;               // value already used

    s_valueSet.insert(value);
    return true;
}
