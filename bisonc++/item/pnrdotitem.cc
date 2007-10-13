#include "item.ih"

std::ostream &Item::pNrDotItem(std::ostream &out) const
{
    Production const *prod = production();

    if (!prod)
        return out;

    out << "[P" << prod->nr() << " " << dot() << "] ";

    return insert(out, prod);
}
