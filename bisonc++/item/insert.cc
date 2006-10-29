#include "item.ih"

ostream &Item::insert(ostream &out, Production const *prod) const
{
    OM::InsType type = OM::type();
    OM::setType(OM::STD);

    out << prod->lhs()->name() << " -> ";

    copy(prod->begin(), prod->begin() + dot(), 
             ostream_iterator<Symbol const *>(out, " "));

    out << " . ";

    copy(prod->begin() + dot(), prod->end(),
         ostream_iterator<Symbol const *>(out, " "));

    OM::setType(type);

    return out;
}
