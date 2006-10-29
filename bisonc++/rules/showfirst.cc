#include "rules.ih"

void Rules::showFirst() const
{
    if (!Arg::instance().option(0, "construction"))
        return;

    msg() << info;

    msgstream() << "FIRST sets:\n";

    OM::setType(OM::EXTENDED);

    copy(d_nonTerminal.begin(), d_nonTerminal.end(), 
                ostream_iterator<NonTerminal const *>(msgstream(), "\n"));

    OM::setType(OM::STD);

    msgstream() << info;
}







