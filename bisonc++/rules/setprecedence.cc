#include "rules.ih"

void Rules::setPrecedence(Terminal const *terminal)
{
    if (!d_currentProduction->precedence())
    {
        d_currentProduction->setPrecedence(terminal);
        terminal->used();
    }
    else
        msg() << "%prec " << terminal << ": precedence already set to " <<
                &Terminal::quotedName << 
                d_currentProduction->precedence() << 
                &Terminal::plainName << err;
}
