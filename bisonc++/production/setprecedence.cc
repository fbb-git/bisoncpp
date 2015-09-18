#include "production.hh"

void Production::setPrecedence(Terminal const *terminal) 
{
    d_precedence = terminal;
}
