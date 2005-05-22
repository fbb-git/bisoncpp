#include "production.ih"

Symbol *Production::vectorIdx(unsigned idx) const
{
    return idx >= size() ? 0 : std::vector<Symbol *>::operator[](idx);
}
