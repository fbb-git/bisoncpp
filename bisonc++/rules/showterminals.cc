#include "rules.ih"

void Rules::showTerminals() const
{
    if (!Msg::display())
        return;

    msg() << info;
           
    msgstream() << "Symbolic Terminal tokens:\n";

    Terminal::inserter(&Terminal::valueQuotedName);

    copy(d_terminal.begin(), d_terminal.end(), 
                ostream_iterator<Terminal const *>(msgstream(), "\n"));

    msgstream() << info;
}
