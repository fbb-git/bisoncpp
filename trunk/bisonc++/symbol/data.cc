#include "symbol.ih"

std::ostream &(Symbol::*Symbol::s_insert[])(std::ostream &out) const =
{
    &Symbol::raw,
    &Symbol::standard,
    &Symbol::withType,      // EXTENDED
    &Symbol::standard,      // SPECIAL
};
