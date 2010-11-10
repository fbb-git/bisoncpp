#include "symbol.ih"

Symbol::Symbol(string const &name, Type type, string const &stype)
:
    d_name(name),
    d_stype(stype),
    d_type(type),
    d_used(false)
{}
