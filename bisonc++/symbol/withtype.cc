#include "symbol.ih"

ostream &Symbol::withType(ostream &out) const
{
    return out << (d_type == NON_TERMINAL ? "Nonterminal" : "Terminal") << 
                  " `" << d_name << "'";
}
