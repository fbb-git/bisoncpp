#include "production.ih"

void Production::setPrecedence(Terminal const *terminal) 
{
    d_precedence = terminal;
}
