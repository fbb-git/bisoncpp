#include "terminal.ih"

ostream &Terminal::srTable(ostream &out) const
{
    if (isReserved())
        return out << d_readableLiteral;

    return out << setw(3) << value();
}
