#include "rules.ih"

void Rules::showFirst() const
{
    if (!Arg::instance().option(0, "construction"))
        return;

    msg() << info;

    msgstream() << "FIRST sets:\n";

    NonTerminal::inserter(&NonTerminal::nameAndFirstset);
    Terminal::inserter(&Terminal::plainName);

    copy(d_nonTerminal.begin(), d_nonTerminal.end(), 
                ostream_iterator<NonTerminal const *>(msgstream(), "\n"));

    msgstream() << info;
}







