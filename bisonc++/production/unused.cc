#include "production.ih"

void Production::unused(Production const *production)
{
    if (!production->d_used)
    {
        if (!s_unused)
        {
            wmsg << 
                "Unused production rule(s):" << endl;
            wmsg.setTag("");
            s_unused = true;
        }
        wmsg << "  " << production << endl;
    }
}
