#include "rules.ih"

void Rules::showTerminals() const
{
    if (!imsg.isActive())
        return;

    imsg.setTag("");

    imsg << "\n"
            "Symbolic Terminal tokens:\n";

    Terminal::inserter(&Terminal::valueQuotedName);

    copy(d_terminal.begin(), d_terminal.end(), 
                ostream_iterator<Terminal const *>(imsg, "\n"));

    imsg << endl;
}
