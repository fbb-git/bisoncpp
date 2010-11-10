#include "production.ih"

Symbol *Production::vectorIdx(size_t idx) const
{
    return idx >= size() ? 0 : std::vector<Symbol *>::operator[](idx);
}
