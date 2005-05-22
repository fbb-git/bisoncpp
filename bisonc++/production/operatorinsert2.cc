#include "production.ih"

std::ostream &operator<<(std::ostream &out, Production const *production)
{
    return out << "    " << production->d_nr << ": " << *production;
}

