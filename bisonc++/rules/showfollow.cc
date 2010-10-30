#include "rules.ih"

void Rules::showFollow() const
{
    if (!Arg::instance().option(0, "construction"))
        return;

    imsg << "\n"
            "FOLLOW sets:\n";

    NonTerminal::inserter(&NonTerminal::nameAndFollowset);

    copy(d_nonTerminal.begin(), d_nonTerminal.end(), 
                ostream_iterator<NonTerminal const *>(imsg, "\n"));

    imsg << endl;
}
