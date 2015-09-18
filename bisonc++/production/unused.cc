#include "production.hh"

void Production::unused(Production const *production)
{
    if (!production->d_used)
    {
        if (!s_unused)
        {
            Global::plainWarnings();
            wmsg << 
                "Unused production rule(s):" << endl;
            s_unused = true;
        }
        wmsg << "  " << production << endl;
    }
}
