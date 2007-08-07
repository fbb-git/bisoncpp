#include "production.ih"

Symbol *Production::vectorIdx(size_t/*unsigned*/ idx) const
{
    return idx >= size() ? 0 : std::vector<Symbol *>::operator[](idx);
}
