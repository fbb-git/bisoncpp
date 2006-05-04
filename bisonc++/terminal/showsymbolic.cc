#include "terminal.ih"

void Terminal::showSymbolic(Terminal const *term)
{
    msg() << term->value() << ": " << term << info;
}
