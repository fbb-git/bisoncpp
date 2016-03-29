#include "atdollar.ih"

bool AtDollar::stackElement() const
{
    switch (d_pattern)
    {
        case AA:
        case DD:
        case refDD:
        case DDm:
        case DDp:
        case DDpar:
        return false;

        default:
        return true;
    }
}
        
