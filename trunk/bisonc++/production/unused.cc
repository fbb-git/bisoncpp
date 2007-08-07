#include "production.ih"

void Production::unused(Production const *production)
{
    if (!production->d_used)
    {
        if (!s_unused)
        {
            msg() << 
                "Unused production rule(s):" << warning;
            Msg::setWarning("");
            s_unused = true;
        }
        msg() << "  " << production << warning;
    }
}
