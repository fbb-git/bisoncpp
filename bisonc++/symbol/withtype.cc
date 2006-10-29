#include "symbol.ih"

ostream &Symbol::withType(ostream &out) const
{
    return out << (d_type == NON_TERMINAL ? "Non-terminal" : "Terminal") << 
                  " `" << d_name << "'";
}
