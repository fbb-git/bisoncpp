#include "rules.ih"

void Rules::showFollow() const
{
    if (!Arg::instance().option(0, "construction"))
        return;

    msg() << info;

    msgstream() << "FOLLOW sets:\n";

    NonTerminal::inserter(&NonTerminal::nameAndFollowset);

    copy(d_nonTerminal.begin(), d_nonTerminal.end(), 
                ostream_iterator<NonTerminal const *>(msgstream(), "\n"));

    msgstream() << info;
}
