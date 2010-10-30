#include "terminal.ih"

void Terminal::setValue(size_t value)
{
    if (!setUnique(value))                
        emsg << "Value " << value << " of token " << this << 
                     " multiply assigned " << endl;
    
    s_valueSet.erase(d_value);
    s_value = value + 1;

    d_value = value;
}
