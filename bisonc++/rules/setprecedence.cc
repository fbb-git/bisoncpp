#include "rules.ih"

void Rules::setPrecedence(Terminal const *terminal)
{
    if (!d_currentProduction->precedence())
    {
        d_currentProduction->setPrecedence(terminal);
        terminal->used();
    }
    else
        msg() << "%prec " << terminal->literal() << 
            ": precedence already set to `" << 
            d_currentProduction->precedence()->literal() << "'" << err;
}
