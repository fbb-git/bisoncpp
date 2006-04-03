#include "terminal.ih"

unsigned        Terminal::s_priority;
set<unsigned>   Terminal::s_valueSet;
unsigned        Terminal::s_value = Terminal::INITIAL_SYMBOLIC_VALUE;
unsigned        Terminal::s_maxValue;
unsigned        Terminal::s_nActive;

char const *Terminal::s_association[] = 
{
    "",                   // UNDEFINED,
    "non-associative",    // NONASSOC,
    "left associative",   // LEFT,
    "right associative",  // RIGHT
};
