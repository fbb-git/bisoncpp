#include "terminal.hh"

ostream &Terminal::nameOrValue(ostream &out) const
{
    if (isReserved())
        return out << d_readableLiteral;

    return out << setw(3) << value();
}
