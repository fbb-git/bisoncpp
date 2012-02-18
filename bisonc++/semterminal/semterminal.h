#ifndef INCLUDED_SEMTERMINAL_
#define INCLUDED_SEMTERMINAL_

#include "../sembase/sembase.h"
class Terminal;

class SemTerminal: public SemBase
{
    Terminal *d_terminal;

    public:
        SemTerminal(Terminal *terminal);    // not owned by SemTerminal!
        operator Terminal *() const;
};

inline SemTerminal::SemTerminal(Terminal *terminal)
:
    SemBase(Tag::TERMINAL),
    d_terminal(terminal)
{}

inline SemTerminal::operator Terminal *() const
{
    return d_terminal;
}

template <>
struct Type<SemEnum::Tag::TERMINAL>
{
    typedef SemTerminal const &conversionType;
    typedef Terminal *semType;
};

        
#endif
