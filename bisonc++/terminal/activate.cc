#include "terminal.ih"

void Terminal::activate() 
{
    if (d_status == NOT_ACTIVE)
    {
        d_status = ACTIVE;
        ++s_nActive;
        lineMsg() << d_readableLiteral << ": (active: " << s_nActive << ")" <<
                     info;
    }
}
