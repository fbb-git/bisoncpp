#include "terminal.ih"

void Terminal::unused(Terminal const *terminal)
{
    static bool header = false;

    if (!terminal->isUsed())
    {
        if (!header)
        {
            wmsg << "Terminal symbol(s) not used in productions:" << endl;
            header = true;
        }

        wmsg << terminal << endl;
    }
}
