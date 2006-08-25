#include "terminal.ih"

size_t/*unsigned*/        Terminal::s_priority;
set<size_t/*unsigned*/>   Terminal::s_valueSet;
size_t/*unsigned*/        Terminal::s_value = Terminal::INITIAL_SYMBOLIC_VALUE;
size_t/*unsigned*/        Terminal::s_maxValue;

char const *Terminal::s_association[] = 
{
    "",                   // UNDEFINED,
    "non-associative",    // NONASSOC,
    "left associative",   // LEFT,
    "right associative",  // RIGHT
};
