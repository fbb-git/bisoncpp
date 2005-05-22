#include "state.ih"

void State::showAction(Terminal const *terminal, ShiftReduce const &action, 
                       bool block) const
{
    string const &name = terminal->display();

    msg() << "    " << (block ? "[" : "") <<
            "on " << name << left <<
            setw(max(10 - static_cast<int>(name.length()), 1)) << 
            ":" << spool;

    if (action.accept())
        msg() << "ACCEPT" << spool;
    else if (action.shift())
        msg() << "shift, and go to state " << action.state() << spool;
    else 
        msg() << "reduce, using production\n" << 
                setw(12) << " " << action.production() << spool;

    msg() << (block ? "]" : "") << info;
}




