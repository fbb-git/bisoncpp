#include "state.ih"

void State::showGoTo() const
{
    if (!d_goto.size())
        return;

    for                             // first: NonTerminal const *
    (                               // second: state number
        GoToTableConstIter it = d_goto.begin();
            it != d_goto.end();
                ++it
    )
    {
        string const &name = it->first->name();

        msg() << "    on " << name << left <<
            setw(max(10 - static_cast<int>(name.length()), 1)) << 
            ":" << "shift, and go to state " << it->second << info;
    }
}
