#include "production.ih"

std::ostream &Production::standard(std::ostream &out) const
{
    out << d_nr << ": " << lhs();

    if (d_precedence != 0)
        out << " (" << d_precedence << ')';

    out << " -> ";

    if (size() == 0)
        out <<  " <empty>";
    else
    {
        for (const_iterator sym = begin(); sym != end(); ++sym)
            out << ' ' << *sym;
    }

    return out;
}
