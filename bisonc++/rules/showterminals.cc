#include "rules.ih"

void Rules::showTerminals() const
{
    if (!Msg::display())
        return;

    msg() << info;
           
    msgstream() << "Symbolic Terminal tokens:\n";

    OM::setType(OM::SPECIAL);

    copy(d_terminal.begin(), d_terminal.end(), 
                ostream_iterator<Terminal const *>(msgstream(), "\n"));

    OM::setType(OM::STD);

    msgstream() << info;
}
