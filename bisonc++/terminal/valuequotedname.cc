#include "terminal.ih"

std::ostream &Terminal::valueQuotedName(std::ostream &out) const
{
    if (isReserved())
        return out << "       " << name();

    return out << "   " << setw(3) << value() << ": " << d_readableLiteral;
}
