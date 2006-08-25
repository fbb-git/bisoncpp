#include "terminal.ih"

void Terminal::setValue(size_t/*unsigned*/ value)
{
    if (!setUnique(value))                
        msg() << "Value " << value << " of token " << name() << 
                     " multiply assigned " << err;
    
    s_valueSet.erase(d_value);
    s_value = value + 1;

    d_value = value;
}
