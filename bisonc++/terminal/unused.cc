#include "terminal.ih"

void Terminal::unused(Terminal const *terminal)
{
    static bool header = false;

    if (!terminal->isUsed())
    {
        if (!header)
        {
            msg() << 
                "Terminal symbol(s) not used in productions:" << warning;
            Msg::setWarning("");
            header = true;
        }
        msg() << "  " << terminal->display() << warning;
    }
}
