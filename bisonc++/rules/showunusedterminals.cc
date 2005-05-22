#include "rules.ih"

void Rules::showUnusedTerminals() const
{
    for_each(d_terminal.begin(), d_terminal.end(), &Terminal::unused);

    msg() << info;

    Msg::setWarning();
}
