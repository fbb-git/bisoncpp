#include "nonterminal.ih"

std::ostream &NonTerminal::insName(std::ostream &out) const
{
    std::string const &nName = name();

    return out << "   " << nName << left <<
            setw(max(10 - static_cast<int>(nName.length()), 1)) << ": ";
}
