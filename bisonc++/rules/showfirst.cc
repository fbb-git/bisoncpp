#include "rules.ih"

void Rules::showFirst() const
{
    if (!Arg::instance().option(0, "construction"))
        return;

    imsg << "\n"
            "FIRST sets:\n";

    NonTerminal::inserter(&NonTerminal::nameAndFirstset);
    Terminal::inserter(&Terminal::plainName);

    copy(d_nonTerminal.begin(), d_nonTerminal.end(), 
                ostream_iterator<NonTerminal const *>(imsg, "\n"));

    imsg << endl;
}







