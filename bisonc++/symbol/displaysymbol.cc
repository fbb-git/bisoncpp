#include "symbol.ih"

void Symbol::displaySymbol(Symbol const *sp)
{
    msg() << sp << " " << spool;
}
