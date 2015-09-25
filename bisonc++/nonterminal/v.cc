#include "nonterminal.ih"

size_t NonTerminal::v_value() const
{
    return d_nr;
}

FirstSet const &NonTerminal::v_firstSet() const
{
    return d_first;
}

std::ostream &NonTerminal::insert(std::ostream &out) const
{
    return (this->*NonTerminal::s_insertPtr)(out);
}

