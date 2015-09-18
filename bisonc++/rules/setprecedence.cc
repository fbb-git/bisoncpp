#include "rules.hh"

void Rules::setPrecedence(Terminal const *terminal)
{
    if (!d_currentProduction->precedence())
    {
        d_currentProduction->setPrecedence(terminal);
        terminal->used();
    }
    else
        emsg << "%prec " << terminal << ": precedence already set to " <<
                &Terminal::quotedName << 
                d_currentProduction->precedence() << 
                &Terminal::plainName << endl;
}
