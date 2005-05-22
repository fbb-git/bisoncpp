#include "symtab.ih"

Symbol *Symtab::lookup(std::string const &symbol)
{
    iterator it = find(symbol);

    return it == end() ? 0 : it->second;
}
