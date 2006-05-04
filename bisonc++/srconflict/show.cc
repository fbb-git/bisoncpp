#include "srconflict.ih"

void SRConflict::show(SRConflict const &conflict)
{
    msg() << nlindent <<  
            "On `" << conflict.d_symbol->display() << "' to state " << 
                                           conflict.d_state << "\n" <<
            indent << "or reduce using " << conflict.d_production << "\n" <<
            indent << "solved as SHIFT (by default)" << info;
}
