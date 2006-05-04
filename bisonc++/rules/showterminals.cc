#include "rules.ih"

void Rules::showTerminals() const
{
    msg() << "\n"
            "Symbolic Terminal tokens:\n" << 
            info;

    for_each(d_terminal.begin(), d_terminal.end(), &Terminal::showSymbolic);

    msg() << info;
}
