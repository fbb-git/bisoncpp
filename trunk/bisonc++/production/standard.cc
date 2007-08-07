#include "production.ih"

std::ostream &Production::standard(std::ostream &out) const
{
    out << d_nr << ": " << lhs() << " -> ";

    if (!size())
        return out <<  " <empty>";

    for (const_iterator sym = begin(); sym != end(); ++sym)
        out << " " << *sym;

    return out;
}
