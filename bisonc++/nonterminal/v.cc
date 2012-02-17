#include "nonterminal.ih"

inline size_t NonTerminal::v_size() const
{
    return d_nr;
}

std::ostream &NonTerminal::insert(std::ostream &out) const
{
    return (this->*NonTerminal::s_insertPtr)(out);
}

