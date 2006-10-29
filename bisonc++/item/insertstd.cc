#include "item.ih"

ostream &Item::insertStd(ostream &out) const
{
    Production const *prod = production();

    if (!prod)
        return out;

    out << prod->nr() << ": ";

    return insert(out, prod);
}
