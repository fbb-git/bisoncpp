#include "terminal.ih"

void Terminal::setValue(size_t value)
{
    if (!setUnique(value))                
        msg() << "Value " << value << " of token " << this << 
                     " multiply assigned " << err;
    
    s_valueSet.erase(d_value);
    s_value = value + 1;

    d_value = value;
}
